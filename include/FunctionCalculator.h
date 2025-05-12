#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <optional>
#include <iostream>
#include "InputException.h"
#include <sstream>
#include <fstream>

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
            //check if m_operations.size() +1(this) > userChoiseOperations // if yes to throw exception
            m_operations.push_back(std::make_shared<FuncType>(m_operations[*f0], m_operations[*f1]));
        }
    }

    template <typename FuncType>
    void unaryFunc()
    {
         //check if m_operations.size() +1(this) > userChoiseOperations // if yes to throw exception
    	m_operations.push_back(std::make_shared<FuncType>());
	}
    template <typename FuncType>
    void unaryWithIntFunc()// this is for scal operation
    {
        int i = 0;
      //  m_istr >> i;
        m_iss >> i;
       //    I need to check that i is int

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

    std::optional<int> readOperationIndex() ;
    Action readAction() ;

    void runAction(Action action);

    ActionMap createActions() const;
    OperationList createOperations() const ;

    bool m_readingFromFile = false;
    void readLine();
    std::string m_line;
    std::istringstream m_iss;
	std::ifstream m_file;
    void readInput();
   // m_stream;
    //
};
