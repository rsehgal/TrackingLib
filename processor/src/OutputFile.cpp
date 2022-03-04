/*
**	Filename : OutputFile.cpp
**	2022-03-04
**	username : rsehgal
*/

#include "OutputFile.h"
#include "TFile.h"
#include <iostream>
namespace lite_interface{

OutputFile *OutputFile::s_instance = 0;

OutputFile::OutputFile() {
	// TODO Auto-generated constructor stub

}

OutputFile::~OutputFile() {
	// TODO Auto-generated destructor stub
}

OutputFile* OutputFile::instance(std::string filename) {
        if (!s_instance)
          s_instance = new OutputFile(filename);
        return s_instance;
}

OutputFile* OutputFile::instance() {
        if (s_instance)
          return s_instance;
        else{
        	std::cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        	std::cout<<"@@ Instance of Output class does not exist in Memory, please create it first....@@" << std::endl;
        	std::cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        }
}

OutputFile::OutputFile(std::string fileName) {
	fFileName = fileName;
	fp = new TFile(fFileName.c_str(),"RECREATE");
}

void OutputFile::Close(){
	fp->Close();
}

TFile* OutputFile::GetOutputFilePtr()const{
	return fp;
}

void OutputFile::cd(){
	fp->cd();
}
} /* end of lite_interface */
