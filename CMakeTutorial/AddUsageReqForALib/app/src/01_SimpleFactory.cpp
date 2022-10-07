#include <cmath>
#include <cfloat>

#include <exception>
#include <stdexcept>
#include <iostream>

#include "01_SimpleFactory.h"

namespace SimpleFactoryModel
{
    using logic_err = std::logic_error;

    void Operate::setFirstNum(double num)
    {
        numA = num;
    }

    double Operate::getFirstNum(void)
    {
        return numA;
    }

    void Operate::setSecondNum(double num)
    {
        numB = num;
    }

    double Operate::getSecondNum(void)
    {
        return numB;
    }

    Operate::Operate(void)
    {
        numA = 0.0f;
        numB = 0.0f;
    }

    double Operate_Add::getResult(void)
    {
        return getFirstNum() + getSecondNum();
    }

    double Operate_Sub::getResult(void)
    {
        return getFirstNum() - getSecondNum();
    }

    double Operate_Mul::getResult(void)
    {
        return getFirstNum() * getSecondNum();
    }

    double Operate_Div::getResult(void)
    {
        double result = 0.0f;
        double second = 0.0f;

        second = getSecondNum();
        if (fabs(second) < DBL_EPSILON)
        {

            throw logic_err("Divide by zero.");
        }
        else
        {
            result = getFirstNum() / second;
        }

        return result;
    }

    Operate *Operate_Factory::createOperate(OperateType type)
    {
        Operate *ptr = nullptr;
        switch (type)
        {
        case op_add:
            ptr = new Operate_Add();
            break;
        case op_sub:
            ptr = new Operate_Sub();
            break;
        case op_mul:
            ptr = new Operate_Mul();
            break;
        case op_div:
            ptr = new Operate_Div();
            break;
        default:
            break;
        }
        if (ptr == nullptr)
        {
            throw logic_err("Invalid operate type.");
        }
        return ptr;
    }

} // namespace SimpleFactoryModel

void UseSimpleFactoryModel(void)
{
    using namespace SimpleFactoryModel;

    Operate_Factory fac;
    OperateType type;
    Operate *op = nullptr;
    double result = 0.0f;
    for (type = op_add; type < op_max; type = static_cast<OperateType>(type + 1))
    {
        op = fac.createOperate(type);

        if (op != nullptr)
        {
            op->setFirstNum(10.0f);
            op->setSecondNum(0.0f);

            try
            {
                result = op->getResult();
            }
            catch (logic_err &e)
            {
                std::cout << e.what() << std::endl;
            }

            std::cout << type << " " << result << std::endl;
        }
    }
}