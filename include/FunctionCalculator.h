#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <optional>
#include <iostream>


class Operation;


class FunctionCalculator
{
public:
    FunctionCalculator(std::istream& istr, std::ostream& ostr);
    void run();

private:
    void eval();
    void del();
    void help();
    void exit();

    template <typename FuncType>
    void binaryFunc()
    {
        // first the function check that the index are good and than creating the operation with pointer to the num of index
        if (auto f0 = readOperationIndex(), f1 = readOperationIndex(); f0 && f1)
        {
            m_operations.push_back(std::make_shared<FuncType>(m_operations[*f0], m_operations[*f1]));
        }
    }

    template <typename FuncType>
    void unaryFunc()
    {
        //firs i need to check that is good index
    	m_operations.push_back(std::make_shared<FuncType>());
	}
    template <typename FuncType>
    void unaryWithIntFunc()
    {
        int i = 0;
        //i need to make sore that i its rally int and in spacepic range
        m_istr >> i;
        m_operations.push_back(std::make_shared<FuncType>(i));
    }
    void printOperations() const;

    enum class Action
    {
        Invalid,
        Eval,
        Iden,
        Tran,
        Scal,
        Sub,
        Add,
        Mul,
        Comp,
        Del,
        Help,
        Exit,
    };

    struct ActionDetails
    {
        std::string command;
        std::string description;
        Action action;
    };

    using ActionMap = std::vector<ActionDetails>;
    using OperationList = std::vector<std::shared_ptr<Operation>>;

    const ActionMap m_actions;
    OperationList m_operations;
    bool m_running = true;
    std::istream& m_istr;
    std::ostream& m_ostr;

    std::optional<int> readOperationIndex() const;
    Action readAction() const;

    void runAction(Action action);

    ActionMap createActions() const;
    OperationList createOperations() const ;
};
