/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "FotoScherm.h"

FotoScherm::FotoScherm()
{
	//het optiescherm
	this->optieScherm = new OptieScherm( this );

	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	int scrWidth = EXTENT_X(screenSize);
	int scrHeight = EXTENT_Y(screenSize);

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	this->achtergrondLabel = new Label(0,0, scrWidth, scrHeight, NULL, "Achtergrond", 0xE0E0E0, font);

	//maak een plaatje (laden uit de resource file res.lst) en voeg label als parent toe
	image = new Image(0, 0, 100, 100, achtergrondLabel, true, true, RES_IMAGE);

	//maak tekst bij het plaatje met een label
	this->imageTekst = new Label(0, 0, 70, 80, achtergrondLabel, "My Label", 0x000000, font);

	//stel dit scherm in als het main scherm, met achtergrondlabel als de basis widget
	this->setMain( this->achtergrondLabel );
}


FotoScherm::~FotoScherm()
{

}


//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );

	//haal informatie imagetekst op van optiescherm
	this->imageTekst->setCaption( this->optieScherm->getImagetekst() );
//	/this->imageTekst->setCaption("Test Tekst");
}



//afvangen invoer
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
}

void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	//bij touch, laat optiescherm zien
}


