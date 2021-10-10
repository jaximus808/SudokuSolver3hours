#include <iostream>   
#include <cmath>  
#include <random>
#include <time.h>     


class Sudoku
{
    public:
        int *layout = new int(81);
        float random(float _max)
        {
            float _rand = sin(2000000.0 + time(NULL) * rand());
            return (std::abs(_rand - floor(_rand)))*_max;
        }
        
        bool LegalCheck(int _pos, int _value)
        {
            //collum check
            //std::cout << _value << " " << _pos<< "\n";
            for(int i = 0; i < 9; i++) if(layout[(_pos-(_pos/9)*9) + i*9] == _value) return false;

            //row check
            for(int i = 0; i < 9; i++) if(layout[((_pos/9)*9) + i] == _value) return false;
            for(int i = 0; i < 3; i++)
            {
                //(((((_pos/9)*9)/27)+i*9)*27 + 3*(((_pos-(_pos/9)*9))/3)) + y
                for(int y = 0; y < 3; y++) 
                {
                    //std::cout<< ((_pos/27)*27) + 3*((_pos-(_pos/9)*9)/3) + 9*i + y << " ";
                    if( layout[ (((_pos/27)*27) + 3*((_pos-(_pos/9)*9)/3) + 9*i) + y ] == _value) return false; 
                }
                //std::cout<< ((_pos/27)*27) + 3*((_pos-(_pos/9)*9)/3) + 9*i;
            }
            //std::cout<<"\n";
            return true; 
        }

        Sudoku()
        {
            for(int i = 0; i < 81; i++) layout[i] = 0;
            
            for(int i = 0; i < 81; i++)
            {
                float placeChance = random(1);
                if(placeChance > 0.7) 
                {
                    //need to do a sudokue legal move check
                    int potValue = ((int)random(8))+1;
                    if(LegalCheck(i, potValue)) layout[i] = potValue;
                }
                //std::cout << layout[i];
            }
        }
        void PrintLayout()
        {
            std::cout << "\nprinting board\n";
            std::cout << "----------------------\n";
            for(int i = 0; i < 81; i++)
            {
                std::cout<<layout[i] << " ";
                if((i+1) % 9 == 0) 
                {
                    std::cout << "\n";
                    if((i+1) %27 == 0) std::cout << "----------------------\n";
                }  
                else if((i+1) % 3 == 0) std::cout<< "| ";
            }
        }

        //recursion time
        bool Solve(int _pos, bool _toPrint)
        {
            if(_toPrint) 
            {
                PrintLayout();
                std::cout << _pos << "\n";
                if(_pos == 81) std::cout<< "done"; 
            }
            
            
            if(_pos == 81) return true; 
            if(layout[_pos] != 0)
            {
                if(_toPrint) 
                {
                    std::cout<<"occupied num ";
                    std::cout <<layout[_pos] << "\n";
                }
                return Solve(_pos+1,_toPrint);
            } 
            for(int i = 1; i < 10; i++)
            {
                if(LegalCheck(_pos, i)) 
                {
                    if(_toPrint) std::cout<<"attempting " << i << " at pos " << _pos;
                    layout[_pos] = i;
                    bool valid = Solve(_pos+1,_toPrint);
                    if(valid) return true;
                    else layout[_pos] = 0;
                }
                
            }
            layout[_pos] = 0;
            return false; 

        }
          

};

int main()
{
    Sudoku *sudoku = new Sudoku();
    std::cout<<"starting board: \n";
    sudoku->PrintLayout();
    std::string req; 
    std::cout<<"Would you like us to solve this board for you? (n for no, default yes)\n";
    std::cin>>req;
    if(req != "n")
    {
        std::cout<<"would you like each step printed, know it will be slower? (y for yes, default no)";
        std::string pri;
        std::cin >> pri;
        std::cout<< "working on solution\n";
        bool done = sudoku->Solve(0,pri == "y");
        if(!done) std::cout << "error";
        else 
        {
            sudoku->PrintLayout();
            std::cout << "Finished board";
        }
    }
}