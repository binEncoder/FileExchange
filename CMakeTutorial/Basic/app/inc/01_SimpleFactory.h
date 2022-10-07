#pragma once

namespace SimpleFactoryModel
{
    typedef enum
    {
        op_add = 0,
        op_sub,
        op_mul,
        op_div,
        op_max
    } OperateType;

    class Operate
    {
    public:
        Operate(void);
        virtual double getResult(void) = 0;
        void setFirstNum(double num);
        double getFirstNum(void);

        void setSecondNum(double num);
        double getSecondNum(void);

    private:
        double numA, numB;
    };

    class Operate_Add : public Operate
    {
    public:
        // 必须增加在类内部的 getResult 函数声明，否则因为基类中的 getResult 没有默认实现，Visual Studio 不认
        virtual double getResult(void) override;
    };

    class Operate_Sub : public Operate
    {
    public:
        virtual double getResult(void) override;
    };

    class Operate_Mul : public Operate
    {
    public:
        virtual double getResult(void) override;
    };

    class Operate_Div : public Operate
    {
    public:
        virtual double getResult(void) override;
    };

    class Operate_Factory
    {
    public:
        Operate *createOperate(OperateType type);
    };

} // namespace SimpleFactoryModel

void UseSimpleFactoryModel(void);