//Kevin Gallegos 1858764 PA8
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300


int main(int argc, char* argv[]) {
   int token_count, line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   //string delim = " "; 
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and print tokens 
   line_count = 0;
   Dictionary D;
   while( getline(in, line) )  {
      line_count++;
      len = line.length();
      
      // get tokens in this line
      token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      transform(token.begin(), token.end(), token.begin(), ::tolower);
      //cout<<"first token is "<<token<<endl;
      //D.setValue(token,1);
       if(token.length()!=0){
                if(D.contains(token) == false){
                        D.setValue(token,1);
                }
		else{
                	int x = D.getValue(token);
        		D.setValue(token,x+1);
		}
	}
      
      while( token!=""){  // we have a token
         // update token buffer
         tokenBuffer += "   "+token+"\n";
         token_count++;

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
	 transform(token.begin(), token.end(), token.begin(), ::tolower);
	 //cout<<"token grabbed is "<<token<<endl;
	 //cout<<"token length is "<<token.length()<<endl;
	 if(token.length()!=0){
	 	if(D.contains(token) == false){
	 		D.setValue(token,1);
	 	}
	 	else{
		 	int x = D.getValue(token);
		 	D.setValue(token,x+1);
		}
	}
      }
   }
   out<<endl;
   out<<D<<endl;
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

