 #include "TCanvas.h"
 #include "TRandom3.h"
 #include "TGraph.h"
 #include "TMath.h"
 #include "TArc.h"
 #include "Fit/Fitter.h"
 

// Double_t fitf(Double_t *x,Double_t *par) {
//   return sqrt(par[2]*par[2] -(x[0]-par[0])*(x[0]-par[0])) + par[1];
// }


void fitCircle() {


  // TF1 *func = new TF1("fit",fitf,-15,15,3); // функция фитирования
  // func->SetParNames("x0","y0","r");
  // func->SetParLimits(0,-5,5);
  // func->SetParLimits(1,-5,5); 
  // func->SetParLimits(2,10,15); 

  Double_t x[4],y[4];

  x[0] = -12.21;
  y[0] = 1.9;

  x[1] = -0.78;
  y[1] = -9.85;

  x[2] = 10.35;
  y[2] = 1.31;

  x[3] = 0.115;
  y[3] = 12.84;

  TGraph *g = new TGraph(4,x,y);
  g->SetMarkerStyle(20);

  auto chi2Function = [&](const Double_t *par) {
       //minimisation function computing the sum of squares of residuals
       // looping at the graph points
       Int_t np = g->GetN();
       Double_t f = 0;
       Double_t *x = g->GetX();
       Double_t *y = g->GetY();
       for (Int_t i=0;i<np;i++) {
          Double_t u = x[i] - par[0];
          Double_t v = y[i] - par[1];
          Double_t dr = par[2] - std::sqrt(u*u+v*v);
          // Double_t dr = 12.5*12.5 - std::sqrt(u*u+v*v);
          f += dr*dr;
       }
       return f;
    };

    // wrap chi2 funciton in a function object for the fit
    // 3 is the number of fit parameters (size of array par)
    ROOT::Math::Functor fcn(chi2Function,3);
    ROOT::Fit::Fitter  fitter;
 
 
    double pStart[3] = {0,0,10};
    fitter.SetFCN(fcn, pStart);
    fitter.Config().ParSettings(0).SetName("x0");
    fitter.Config().ParSettings(0).SetLimits(-5,5);

    fitter.Config().ParSettings(1).SetName("y0");
    fitter.Config().ParSettings(1).SetLimits(-5,5);

    fitter.Config().ParSettings(2).SetName("R");
    fitter.Config().ParSettings(2).SetLimits(5,20);
 
    // do the fit 
    bool ok = fitter.FitFCN();
    if (!ok) {
       Error("line3Dfit","Line3D Fit failed");
    }   
 
    const ROOT::Fit::FitResult & result = fitter.Result();
    result.Print(std::cout);
 
    //Draw the circle on top of the points

    TCanvas *c1 = new TCanvas("c1","fit",1000,1000);
    c1->cd();

    TArc *arc = new TArc(result.Parameter(0),result.Parameter(1),result.Parameter(2));
    arc->SetFillStyle(0); 
    arc->SetLineColor(kRed);
    arc->SetLineWidth(2);

    g->Draw();
    arc->Draw("same");

}