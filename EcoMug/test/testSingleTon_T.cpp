/*
**	Filename : testSingleTon_T.cpp
**	2022-03-22
**	username : rsehgal
*/
#include "EcoMug.h"
#include "SingleTon_T.h"
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include <TVector3.h>
#include <iostream>
int main(int argc, char *argv[]) {
  TApplication *fApp = new TApplication("Muon", NULL, NULL);
  SingleTon_T<EcoMug> *obj = SingleTon_T<EcoMug>::instance();
  EcoMug *gen = obj->GetTargetObject();

  //std::cout << "Instance number : " << gen->instanceCounter << std::endl;
  gen->SetUseSky();              // plane surface gen->ration
  gen->SetSkySize({{10., 10.}}); // x and y size of the plane
  // (x,y,z) position of the center of the plane
  gen->SetSkyCenterPosition({{0., 0., 20.}});

  // The array storing muon gen->ration position
  std::array<double, 3> muon_position;

  unsigned int number_of_events = 500000;

  TH1F *histTheta = new TH1F("Theta", "Theta", 100, 0., M_PI / 2.);
  TH1F *histZenith = new TH1F("ZenithTheta", "ZenithTheta", 100, 0., M_PI / 2.);
  for (auto event = 0; event < number_of_events; ++event) {
    if (!(event % 100000) & event != 0)
      std::cout << "Processed " << event << ".........." << std::endl;
    gen->Generate();
    muon_position = gen->GetGenerationPosition();
    double muon_p = gen->GetGenerationMomentum();
    double muon_theta = gen->GetGenerationTheta();
    double muon_phi = gen->GetGenerationPhi();

    {
      TVector3 ref(0., 0., -1.);
      TVector3 dir(sin(muon_theta) * cos(muon_phi), sin(muon_theta) * sin(muon_phi), cos(muon_theta));
      double angle = dir.Angle(ref);
      // std::cout << "Muon_Theta : " << muon_theta << " : AngleFromCoord : " << angle << std::endl;
      histZenith->Fill(angle);
    }

    double muon_charge = gen->GetCharge();
    // std::cout << "--------------------------------------" << std::endl;
    /*std::cout << "Position : " << muon_p << std::endl
              << "Momentum : " << muon_p << std::endl
              << "Theta : " << muon_theta << std::endl
              << "Phi : " << muon_phi << std::endl
              << "Charge : " << muon_charge << std::endl;*/
    histTheta->Fill(M_PI - muon_theta);
  }

  TF1 *formula = new TF1("Cos Square", "[0]*pow(cos(x),[1])*sin(x)*cos(x)", 0, M_PI / 2.);
  histTheta->Fit(formula, "r");

  std::cout << "Chisquare : " << formula->GetChisquare() << " : NDF : " << formula->GetNDF() << std::endl;
  std::cout << "Chi2/NDF : " << (formula->GetChisquare() / formula->GetNDF()) << std::endl;
  histTheta->Draw();

  histZenith->Fit(formula, "r");
  new TCanvas("Can_HistZenith", "Can_HistZenith");
  histZenith->Draw();

  /*{
    SingleTon_T<EcoMug> *obj = SingleTon_T<EcoMug>::instance();
    EcoMug *gen = obj->GetTargetObject();
  }
  std::cout << "Instance number : " << gen->instanceCounter << std::endl;
  {
    SingleTon_T<EcoMug> *obj = SingleTon_T<EcoMug>::instance();
    EcoMug *gen = obj->GetTargetObject();
  }
  std::cout << "Instance number : " << gen->instanceCounter << std::endl;*/

  fApp->Run();

  return 0;
}
