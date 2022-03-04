/*
**	Filename : OutputFile.h
**	2022-03-04
**	username : rsehgal
*/
#ifndef OutputFile_h
#define OutputFile_h

#include <TFile.h>
#include <string>

namespace lite_interface {

class OutputFile {

  /*
   * To be used only by the code
   */
  std::string fFileName;
  TFile *fp;
  static OutputFile *s_instance;

public:
  static OutputFile *instance();
  static OutputFile *instance(std::string filename);
  OutputFile();
  OutputFile(std::string fileName);
  void Close();
  virtual ~OutputFile();

  /*
   * Function to return the Muon
   */
  TFile *GetOutputFilePtr() const;
  void cd();
};

} // namespace lite_interface
#endif
