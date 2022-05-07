#pragma once

#include "resource.h"
#include <math.h>

#define PI 3.14159265358979

void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{

}

struct DoublePoint{double x,y;};

class WektorPredkosci
{
	double V;
	double Kat;
public:
	WektorPredkosci(double _V,int Kat_w_stopniach);
	void SetKat(int Kat_w_stopniach);
	void SetKat(double Kat_w_radianach);
	void SetMirrorKatX(void);
	void SetMirrorKatY(void);
	void SetV(double _V);
	double GetDx(double Time);
	double GetDy(double Time);
	double GetV(void);
	double GetKatR(void);
	int GetKatS(void);
};

void WektorPredkosci::SetKat(double Kat_w_radianach)
{
	Kat=Kat_w_radianach;
}

int WektorPredkosci::GetKatS(void)
{
	return (int)(Kat*180/PI);
}

double WektorPredkosci::GetKatR(void)
{
	return Kat;
}

double WektorPredkosci::GetV(void)
{
	return V;
}

void WektorPredkosci::SetV(double _V)
{
	V=_V;
}

void WektorPredkosci::SetMirrorKatY(void)
{
	if(Kat<PI)
		Kat=PI-Kat;
	else
		Kat=3*PI-Kat;
}

void WektorPredkosci::SetMirrorKatX(void)
{
	Kat=2*PI-Kat;
}

double WektorPredkosci::GetDy(double Time)
{
	return V*Time*sin(Kat);
}

double WektorPredkosci::GetDx(double Time)
{
	return V*Time*cos(Kat);
}

void WektorPredkosci::SetKat(int Kat_w_stopniach)
{
	Kat=Kat_w_stopniach*PI/180;
}

WektorPredkosci::WektorPredkosci(double _V,int Kat_w_stopniach)
{
    SetKat(Kat_w_stopniach);
	V=_V;
}
//Koniec klasy WektorPredkosci

//Pocz¹tek klasy Bila

class Bila
{
	DoublePoint wspBili;
	HBRUSH kolorBili;
	HBRUSH kolorZazn;
	RECT ObszarRuchu;
	double mikro;
	double S;
	bool ClickR;
	bool kolor;
	UINT IloscBil;
	UINT NrBili;
	UINT R;
	Bila* ABW;
	Bila* AW;
	Bila* ABN;
public:
	WektorPredkosci* Wp;
	Bila(void);
	Bila(int X,int Y,COLORREF rgb,UINT promien,double _V,int Kat,double _mikro);
	void Tick(HWND hWnd,int dx,int dy);
	void Tick(HWND hWnd);
	void Rysuj(HDC hdc);
	void ZaznaczBile(HWND hWnd,int Xmyszy,int Ymyszy);
	void Klikniecie(HWND hWnd,int Xmyszy,int Ymyszy);
	RECT* GetRectBili(void);
	void SetKolorBili(COLORREF rgb);
	void SetKolorBili(HBRUSH KolorBili);
	void SetWspBili(double X,double Y);
	void SetWspBili(DoublePoint WspBili);
	void SetPromienBili(UINT R);
	void SetObszarRuchu(int X1,int Y1,int X2,int Y2);
	void SetAdresWlasnyBili(Bila* _AW);
	void SetAdresWyzejBili(Bila* _ABW);
	void SetAdresNizejBili(Bila* _ABN);
	void SetIloscBil(UINT iloscBil);
	void SetNrBili(UINT nrBili);
	Bila* GetAdresWlasnyBili(void);
	Bila* GetAdresWyzejBili(void);
	Bila* GetAdresNizejBili(void);
	UINT GetIloscBil(void);
	UINT GetNrBili(void);
	double GetWspBili(bool Xtrue_Yfalse);
	double KatWp(int Xmyszy,int Ymyszy);
	void ZmienIloscBil(UINT iloscBil);
	void DeleteBile(UINT nrBili);
};

void Bila::DeleteBile(UINT nrBili)
{
	if(nrBili>1 && nrBili<IloscBil)
	{
	
	}
}

UINT Bila::GetIloscBil(void)
{
	return IloscBil;
}

UINT Bila::GetNrBili(void)
{
	return NrBili;
}

Bila* Bila::GetAdresNizejBili(void)
{
	return ABN;
}

Bila* Bila::GetAdresWyzejBili(void)
{
	return ABW;
}

Bila* Bila::GetAdresWlasnyBili(void)
{
	return AW;
}

void Bila::ZmienIloscBil(UINT iloscBil)
{
	if(iloscBil>IloscBil)
	{
	}
	else
		if(iloscBil<IloscBil)
		{
		}
	IloscBil=iloscBil;
}

void Bila::SetNrBili(UINT nrBili)
{
	NrBili=nrBili;
}

void Bila::SetIloscBil(UINT iloscBil)
{
	IloscBil=iloscBil;

}

void Bila::SetAdresNizejBili(Bila* _ABN)
{
	ABN=_ABN;
}

void Bila::SetAdresWyzejBili(Bila* _ABW)
{
	ABW=_ABW;
}

void Bila::SetAdresWlasnyBili(Bila* _AW)
{
	AW=_AW;
}

double Bila::KatWp(int Xmyszy,int Ymyszy)
{
	double L=pow(pow(Xmyszy-wspBili.x,2)+pow(Ymyszy-wspBili.y,2),0.5);
	if(wspBili.y<Ymyszy)
		return acos((Xmyszy-wspBili.x)/L);
	else
		return acos((Xmyszy-wspBili.x)/-L)+PI;
}

void Bila::Klikniecie(HWND hWnd,int Xmyszy,int Ymyszy)
{
	if(Wp->GetV()==0 && !kolor && !ClickR)
	{
		ClickR=true;
	}
	else
		if(ClickR)
		{
			ClickR=false;
			Wp->SetKat(KatWp(Xmyszy,Ymyszy));
			Wp->SetV(pow(pow(Xmyszy-wspBili.x,2)+pow(Ymyszy-wspBili.y,2),0.5));
			SetTimer(hWnd,1,50,NULL);
		}
}

void Bila::SetObszarRuchu(int X1,int Y1,int X2,int Y2)
{
	SetRect(&ObszarRuchu,X1,Y1,X2,Y2);
}

double Bila::GetWspBili(bool Xtrue_Yfalse)
{
	if(Xtrue_Yfalse)
		return wspBili.x;
	else
		return wspBili.y;
}

void Bila::Tick(HWND hWnd)
{
	InvalidateRect(hWnd,GetRectBili(),true);
	SetWspBili(Wp->GetDx(0.5)+GetWspBili(true),Wp->GetDy(0.5)+GetWspBili(false));
	if(ObszarRuchu.bottom!=NULL)
	{
		if(Wp->GetDy(0.5)+GetWspBili(false)-R<=ObszarRuchu.top || Wp->GetDy(0.5)+GetWspBili(false)+R>=ObszarRuchu.bottom)
			Wp->SetMirrorKatX();
		if(Wp->GetDx(0.5)+GetWspBili(true)-R<=ObszarRuchu.left || Wp->GetDx(0.5)+GetWspBili(true)+R>=ObszarRuchu.right)
			Wp->SetMirrorKatY();
	}
	if(pow(Wp->GetV(),2.0)>2*mikro*10*S)
	{
		Wp->SetV(pow(pow(Wp->GetV(),2.0)-2*mikro*10*S,0.5));
		S=Wp->GetV()*500/1000;
	}
	else
	{
		Wp->SetV(0);
		KillTimer(hWnd,1);
	}
	InvalidateRect(hWnd,GetRectBili(),true);
}

void Bila::SetWspBili(DoublePoint WspBili)
{
	wspBili.x=WspBili.x;
	wspBili.y=WspBili.y;
}

void Bila::SetWspBili(double X,double Y)
{
	wspBili.x=X;
	wspBili.y=Y;
}

void Bila::SetKolorBili(HBRUSH KolorBili)
{
	kolorBili=KolorBili;
}

void Bila::SetKolorBili(COLORREF rgb)
{
	kolorBili=CreateSolidBrush(rgb);
}

void Bila::ZaznaczBile(HWND hWnd,int Xmyszy,int Ymyszy)
{
	int L=pow(pow((double)Xmyszy-wspBili.x,2)+pow((double)Ymyszy-wspBili.y,2),0.5);
	if(L>R&&!kolor)
	{
		kolor=true;
		InvalidateRect(hWnd,GetRectBili(),true);
	}
	else
		if(L<=R&&kolor)
		{
			kolor=false;
			InvalidateRect(hWnd,GetRectBili(),true);
		}
}

RECT* Bila::GetRectBili(void)
{
	RECT pr;
	SetRect(&pr,wspBili.x-R,wspBili.y-R,wspBili.x+R,wspBili.y+R);
	return &pr;
}

void Bila::Tick(HWND hWnd,int dx,int dy)
{
	InvalidateRect(hWnd,GetRectBili(),true);
	wspBili.x+=dx;
	wspBili.y+=dy;
	InvalidateRect(hWnd,GetRectBili(),true);
}

void Bila::Rysuj(HDC hdc)
{
	if(kolor)
        SelectObject(hdc,kolorBili);
	else
		SelectObject(hdc,kolorZazn);
	Ellipse(hdc,wspBili.x-R,wspBili.y-R,wspBili.x+R,wspBili.y+R);
}

Bila::Bila(void)
{
}

Bila::Bila(int X,int Y,COLORREF rgb,UINT promien,double _V,int Kat,double _mikro)
{
	wspBili.x=X;
	wspBili.y=Y;
	kolorBili=CreateSolidBrush(rgb);
	kolorZazn=CreateSolidBrush(RGB(10,10,10));
	R=promien;
	Wp=new WektorPredkosci(_V,Kat);
	kolor=true;
	mikro=_mikro;
	ClickR=false;
	S=0;
	IloscBil=1;
	NrBili=1;
}

//Koniec klasy Bila

class Bile 
{
	UINT iloscBil;
	RECT obszarRuchu;
	
};