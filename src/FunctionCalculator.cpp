#include "FunctionCalculator.h"
#include "SquareMatrix.h"
#include "Add.h"
#include "Sub.h"
#include "Comp.h"
#include "Identity.h"
#include "Transpose.h"
#include "Scalar.h"

#include <iostream>
#include <algorithm>


FunctionCalculator::FunctionCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_operations(createOperations()), m_istr(istr), m_ostr(ostr)
{
}


void FunctionCalculator::run()//iostream
{
    //ask user num of function

    do
    {
        m_ostr << '\n';
        printOperations();
        m_ostr << "Enter command ('help' for the list of available commands): ";
        try {
             readLine();
             const auto action = readAction();
             runAction(action);
    }
        catch(const InputException& exception){
              //...
           std:: cout <<  exception.what();

         }
        //m_redingFromFile
    } while (m_running);
}


void FunctionCalculator::eval()
{
    if (auto index = readOperationIndex(); index)
    {
        const auto& operation = m_operations[*index];
		int inputCount = operation->inputCount();
        int size = 0;
       // m_istr >> size;
        m_iss >> size;//i need to check that is really number
		auto matrixVec = std::vector<Operation::T>();
        if (inputCount > 1)
            m_ostr << "\nPlease enter " << inputCount << " matrices:\n";

		for (int i = 0; i < inputCount; ++i)// in this for he creating the input matrix he first creating the matrix and than he puts the values in the matrix. i need to changhed it 
		{
            auto input = Operation::T(size);// he first creating the matrix here. and than puts values  but why ??
            m_ostr << "\nEnter a " << size << "x" << size << " matrix:\n";
           // m_istr >> input;
            readInput();
            m_iss >> input;
			matrixVec.push_back(input);//

		}
        m_ostr << "\n";
        operation->print(m_ostr, matrixVec);
        m_ostr << " = \n" << operation->compute(matrixVec);
    }
}


void FunctionCalculator::del()
{
    if (auto i = readOperationIndex(); i)
    {
        m_operations.erase(m_operations.begin() + *i);
    }
}


void FunctionCalculator::help()
{
    m_ostr << "The available commands are:\n";
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command << action.description << '\n';
    }
    m_ostr << '\n';
}


void FunctionCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}


void FunctionCalculator::printOperations() const
{
    //to add nunber of legal operation
    m_ostr << "List of available matrix operations:\n";
    for (decltype(m_operations.size()) i = 0; i < m_operations.size(); ++i)
    {
        m_ostr << i << ". ";
        m_operations[i]->print(m_ostr,true);
        m_ostr << '\n';
    }
    m_ostr << '\n';
}


std::optional<int> FunctionCalculator::readOperationIndex() 
{
    int i = 0;
    m_iss >> i;
   // if (!isdigit(i)) throw InputException("You didnt Enter digit in  ");
    if (i >= static_cast<int>(m_operations.size()) )
    {
      //m_ostr << "Operation #" << i << " doesn't exist\n";
        throw InputException("Operation #" + std::to_string(i) +"doesn't exist\n");
        return {};
    }
    return i;
}


FunctionCalculator::Action FunctionCalculator::readAction() 
{
    auto action = std::string();
   // m_istr >> action;
	m_iss >> action;

    const auto i = std::ranges::find(m_actions, action, &ActionDetails::command);
    if (i != m_actions.end())
    {
        return i->action;
    }
     

     throw InputException("number outside the range of the operation vector (Unknown operation)\n");
  //return Action::Invalid;
}


void FunctionCalculator::runAction(Action action)
{
    switch (action)
    {
        default:
            m_ostr << "Unknown enum entry used!\n";
            break;

        case Action::Invalid:
            m_ostr << "Command not found\n";
            break;

        case Action::Eval:         eval();                     break;
        case Action::Add:          binaryFunc<Add>();          break;
        case Action::Sub:          binaryFunc<Sub>();          break;
        case Action::Comp:         binaryFunc<Comp>();         break;
        case Action::Del:          del();                      break;
        case Action::Help:         help();                     break;
        case Action::Exit:         exit();                     break;
        case Action::Iden:          unaryFunc<Identity>();      break;
        case Action::Tran:          unaryFunc<Transpose>();      break;
        case Action::Scal:          unaryWithIntFunc<Scalar>();      break;
          //  m_redingFromFile    /// read() 
          //}
            // resize
    }
}


FunctionCalculator::ActionMap FunctionCalculator::createActions() const
{
    return ActionMap
    {
        {
            "eval",
            "(uate) num n - compute the result of function #num on an n×n matrix "
			"(that will be prompted)",
            Action::Eval
        },
        {
            "scal",
            "(ar) val - creates an operation that multiplies the "
			"given matrix by scalar val",
            Action::Scal
        },
        {
            "add",
            " num1 num2 - creates an operation that is the addition of the result of operation #num1 "
			"and the result of operation #num2",
            Action::Add
        },
         {
            "sub",
            " num1 num2 - creates an operation that is the subtraction of the result of operation #num1 "
			"and the result of operation #num2",
            Action::Sub
        },
        {
            "comp",
            "(osite) num1 num2 - creates an operation that is the composition of operation #num1 "
			"and operation #num2",
            Action::Comp
        },
        {
            "del",
            "(ete) num - delete operation #num from the operation list",
            Action::Del
        },
        {
            "help",
            " - print this command list",
            Action::Help
        },
        {
            "exit",
            " - exit the program",
            Action::Exit
        }
    };
}


FunctionCalculator::OperationList FunctionCalculator::createOperations() const
{
    return OperationList
    {
        std::make_shared<Identity>(),
        std::make_shared<Transpose>(),
    };
}
//--------------------------------------------
void FunctionCalculator::readLine()
{
    m_line.clear();// clear the string for ald things
    if (m_readingFromFile) {
        if (!std::getline(m_file, m_line)) {
          
			// maby to close the file
        }
    }
    else {
        if (!std::getline(std::cin, m_line)) {
			//maybe to throw exception
        }
    }

    m_iss.clear();         // îàôñ îöáéí ÷åãîéí
    m_iss.str(m_line);     // èåòï àú äùåøä äðåëçéú ìÎistringstream
}
//-----------------------------------
void FunctionCalculator::readInput()
{
    if (!(m_iss.eof() || (m_iss >> std::ws).eof())) {
        // maybe the exception will be here
    }

    readLine();
    
}
