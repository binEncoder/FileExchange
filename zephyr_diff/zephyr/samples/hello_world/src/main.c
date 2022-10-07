/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>


#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include <zephyr/devicetree.h>

#define TASK_STACK_SIZE         1024
#define TASK_COUNT              4
#define HEX_DUMP_LENGTH         16

#include "test.h"


K_MUTEX_DEFINE(test_mutex);
K_THREAD_STACK_ARRAY_DEFINE(test_task_stacks, TASK_COUNT, TASK_STACK_SIZE);

K_HEAP_DEFINE(test_heap, 32*1024);

static struct k_thread task[TASK_COUNT];

void test_task(void* p1, void* p2, void* p3)
{
    int task_num = (int)p1, delay_ms;
    size_t idx, numbers;
    char* ptr = (char*)p2;
    for(;;){
        k_mutex_lock(&test_mutex, K_FOREVER);
        printk("Task %d lock mutex...\n", task_num);
        memset(ptr, task_num+0x30, HEX_DUMP_LENGTH);
        LOG_HEXDUMP_WRN(ptr, HEX_DUMP_LENGTH, "Hex Data:");

        // Why need add _PATH postfix ?
        printk("Path of nvic: %s\n", DT_PATH(soc, interrupt_controller_e000e100_PATH));
        printk("Path of uart0( using DT_PATH ): %s\n", DT_PATH(soc, uart_4000c000_PATH));
        printk("Path of uart0( using DT_NODE_PATH & DT_NODELABEL ): %s\n", DT_NODE_PATH(DT_NODELABEL(uart0)));
        printk("Baudrate of uart0( using DT_NODELABEL ): %d\n", DT_PROP(DT_NODELABEL(uart0), current_speed));
        printk("Baudrate of uart0( using DT_ALIAS ): %d\n", DT_PROP(DT_ALIAS(uart_0), current_speed));
        printk("Baudrate of uart0( using DT_INST ): %d\n", DT_PROP(DT_INST(0, ti_stellaris_uart), current_speed));

        numbers = DT_NUM_REGS(DT_NODELABEL(uart0));
        printk("Register number of uart0: %d\n", numbers);
        printk("Register base address of uart0: 0x%08X\n", DT_REG_ADDR_BY_IDX(DT_NODELABEL(uart0), 0));
        printk("Register length of uart0: 0x%08X\n", DT_REG_SIZE_BY_IDX(DT_NODELABEL(uart0), 0));

        numbers = DT_NUM_IRQS(DT_NODELABEL(uart0));
        printk("IRQ number of uart0: 0x%08X\n", DT_IRQ_BY_IDX(DT_NODELABEL(uart0), 0, irq));
        printk("IRQ priority of uart0: 0x%08X\n", DT_IRQ_BY_IDX(DT_NODELABEL(uart0), 0, priority));

        k_mutex_unlock(&test_mutex);
        printk("Task %d unlock mutex...\n", task_num);
        /* __ASSERT(0, "always assert"); */

        delay_ms = 1000*(TASK_COUNT - task_num);
        printk("Task %d sleep %d ms...\n", task_num, delay_ms);
        k_sleep(K_MSEC(delay_ms*50000));
    }
}

void main(void)
{
    void* ptr = k_heap_alloc(&test_heap, HEX_DUMP_LENGTH, K_MSEC(0));
    int idx = 0;

    printk("Hello World! %s\n", CONFIG_BOARD);
    printk("k_heap_alloc return %p\n", ptr);
    printk("test function(1,2) return %d\n", test_function(1, 2));

    for(idx = 0; idx < TASK_COUNT; idx++){
        k_thread_create(
            &task[idx],
            test_task_stacks[idx],
            TASK_STACK_SIZE,
            test_task,
            INT_TO_POINTER(idx),
            ptr,
            NULL,
            K_PRIO_PREEMPT(idx),
            0,
            K_NO_WAIT
        );
    }

    for(idx = 0; idx < TASK_COUNT; idx++){
        k_thread_join(&task[idx], K_FOREVER);
    }

    k_heap_free(&test_heap, ptr);
}
