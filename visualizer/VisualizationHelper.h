/*
 * VisualizationHelper.h
 *
 *  Created on: Apr 28, 2016
 *      Author: rsehgal
 */

#ifndef TEMPLATIZEDINTERFACE_INC_VISUALIZATIONHELPER_H_
#define TEMPLATIZEDINTERFACE_INC_VISUALIZATIONHELPER_H_

#define SHOW_VISUALIZATION
#define USE_EVE

#ifdef SHOW_VISUALIZATION

#ifdef USE_EVE
#include "EveVisualizer.h"
#include "TEveManager.h"
#include "TEveGeoShape.h"
#include "TEveStraightLineSet.h"
#include "TEvePointSet.h"
#include <TGeoMatrix.h>
typedef Tracking::EveVisualizer TomographyVisualizer;
#else
#include "TGeo/Visualizer.h"
typedef Tracking::Visualizer TomographyVisualizer;
#endif

#include "base/Vector3D.h"
#include <TGeoBBox.h>
#include "TApplication.h"
//#include "GlassRpc.h"
//#include "Properties.h"
#include "Track.h"
#include "TGeoManager.h"
// typedef Tomography::Properties Detector;
namespace Tomography {

class Slicer {

  double fXmin, fXmax;
  double fYmin, fYmax;
  double fZmin, fZmax;

public:
  bool fSlicingRequired;

  Slicer() : fSlicingRequired(false), fXmin(0.), fXmax(0.), fYmin(0.), fYmax(0.), fZmin(0.), fZmax(0.) {}

  Slicer(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
      : fSlicingRequired(true), fXmin(xmin), fXmax(xmax), fYmin(ymin), fYmax(ymax), fZmin(zmin), fZmax(zmax)
  {
  }

  bool PointWithinSlice(Tracking::Vector3D<double> pt)
  {
    return pt.x() >= fXmin && pt.x() <= fXmax && pt.y() >= fYmin && pt.y() <= fYmax && pt.z() >= fZmin &&
           pt.z() <= fZmax;
  }

  ~Slicer() {}
};

class VisualizationHelper {

  TomographyVisualizer fVis;
  bool fSlicingRequired;
  // static VisualizationHelper *s_instance;
public:
  VisualizationHelper()
  {
#ifdef USE_EVE
    TEveManager::Create();
#endif
    fSlicingRequired = true;
  }
#ifdef USE_EVE
  void CreatePointSetArray() { fVis.CreatePointSetArray(); }
#endif

  void Register(Track *t) { fVis.AddLine(t->GetP1(), t->GetP2(), t->GetColor()); }

  void Register(std::vector<Tracking::Vector3D<double>> vecOfPt, double color = 5, bool showHitPoints = false)
  {
    if (vecOfPt.size() >= 2) {
      fVis.AddLine(vecOfPt[0], vecOfPt[vecOfPt.size() - 1], color);

      if (showHitPoints) {
        for (unsigned int i = 0; i < vecOfPt.size(); i++) {
          Register(vecOfPt[i]);
        }
      }
    }
    // fVis.AddLine(t->GetP1(),t->GetP2(),t->GetColor());
  }
  void RegisterLine(Tracking::Vector3D<double> p1, Tracking::Vector3D<double> p2) { fVis.AddLine(p1, p2); }

  void Register(Tracking::Vector3D<double> pt) { fVis.AddMarkers(pt); }

#ifdef USE_EVE
  void Register_V2(Tracking::Vector3D<double> pt) { fVis.AddMarkers_V2(pt); }
#endif

#ifdef USE_EVE
  void Lock() { fVis.CloseBins(); }
#endif

  // New overloaded version that also takes slices into consideration
  // and will register the point only if it lie within the slice
  void Register(Slicer slicer, Tracking::Vector3D<double> pt)
  {
    if (slicer.fSlicingRequired) {
      if (slicer.PointWithinSlice(pt)) fVis.AddMarkers(pt);
    }
  }

  std::string GetFileName(std::string geomFile)
  {
    std::string fileName = geomFile.substr(0, geomFile.find(".") - 1);
    std::string ext      = geomFile.substr(geomFile.find(".") + 1);
    if (!ext.compare("gdml")) {
      TGeoManager::Import(geomFile.c_str());
      std::string finalFileName = fileName + ".root";
      gGeoManager->Export(finalFileName.c_str());
      return finalFileName;
    } else {
      if (!ext.compare("root")) {
        return geomFile;
      } else {
        std::cerr << "*************************************" << std::endl;
        std::cerr << "    UnRecognized file format??? " << std::endl;
        std::cerr << "*************************************" << std::endl;
      }
    }
  }

#ifdef USE_EVE
  void InitializeVisualizer() { fVis.InitializeVisualizer(); }
#endif
#ifdef USE_EVE
  // Function to register directly from ROOT file
  void Register(std::string geomFile)
  {
    std::string finalName = GetFileName(geomFile);

    gGeoManager       = gEve->GetGeometry(finalName.c_str());
    int numOfTopNodes = gGeoManager->GetTopVolume()->GetNodes()->GetEntries();
    for (int i = 0; i < numOfTopNodes; i++) {
      std::cout << "Name of : " << i << " Node : " << gGeoManager->GetTopVolume()->GetNodes()->At(i)->GetName()
                << std::endl;
      std::string name = gGeoManager->GetTopVolume()->GetNodes()->At(i)->GetName();
      TGeoNode *node1 =
          gGeoManager->GetTopVolume()->FindNode(gGeoManager->GetTopVolume()->GetNodes()->At(i)->GetName());
      TGeoHMatrix m;
      m.SetDx(node1->GetMatrix()->GetTranslation()[0]); //; = node1->GetMatrix();
      m.SetDy(node1->GetMatrix()->GetTranslation()[1]);
      m.SetDz(node1->GetMatrix()->GetTranslation()[2]);
      // std::cout << node1->GetMatrix()->GetRotationMatrix() << std::endl;
      m.SetRotation(node1->GetMatrix()->GetRotationMatrix());

      TGeoVolume *vol  = node1->GetVolume();
      TGeoShape *shape = vol->GetShape();
      fVis.AddEveShape(name, shape, m, 44);
    }
  }

  void Register(std::string geomFile, std::string placedVolumeName)
  {
    gGeoManager     = gEve->GetGeometry(geomFile.c_str());
    TGeoNode *node1 = gGeoManager->GetTopVolume()->FindNode(placedVolumeName.c_str());
    TGeoHMatrix m;
    m.SetDx(node1->GetMatrix()->GetTranslation()[0]); //; = node1->GetMatrix();
    m.SetDy(node1->GetMatrix()->GetTranslation()[1]);
    m.SetDz(node1->GetMatrix()->GetTranslation()[2]);

    TGeoVolume *vol  = node1->GetVolume();
    TGeoShape *shape = vol->GetShape();
    fVis.AddEveShape(placedVolumeName, shape, m);

    TGeoMatrix *mat = node1->GetMatrix();
    std::cout << "Translation Matrix : " << mat->GetTranslation()[0] << " , " << mat->GetTranslation()[1] << " , "
              << mat->GetTranslation()[2] << std::endl;
    if (!(mat->IsRotation())) std::cout << "NO Rotation" << std::endl;
    // std::cout<<"Rotation Matrix : "<< node1->GetMatrix()->GetRotation() << std::endl;
    double local[3]  = {5., 0., 0.};
    double master[3] = {0., 0., 0.};
    mat->LocalToMaster(local, master);
    std::cout << "W.r.t Local : " << local[0] << " , " << local[1] << " , " << local[2] << std::endl;
    std::cout << "W.r.t Master : " << master[0] << " , " << master[1] << " , " << master[2] << std::endl;
  }
#endif

  void Show()
  {
#ifdef USE_EVE
    Tracking::EveVisualizer::Show();
#else
    fVis.Show();
#endif
  }

  TomographyVisualizer GetVisualizer() { return fVis; }
};

} // namespace Tomography

#endif /* for SHOW_VISUALIZATION */
#endif /* INC_VISUALIZATIONHELPER_H_ */
