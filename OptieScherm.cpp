/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "OptieScherm.h"
#include "Convert.h"

OptieScherm::OptieScherm( Screen* parent )
{
	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//Zet geselecteerde label op NULL
	selectedKleurLabel = NULL;

	//Stel standaard naam van het plaatje in
	tekst = "Plaatje";

	//Stel standaard groote van het plaatje in
	imageGrootte = 100;

	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	int scrWidth = EXTENT_X(screenSize);
	int scrHeight = EXTENT_Y(screenSize);


	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label* backgroundLabel;
	backgroundLabel = new Label(0, 0, scrWidth, scrHeight, NULL, "", 0x9C0000, font);

	//stel achtergrondkleur in
	this->achtergrondKleur = 0xE0E0E0;

	//maak rode knop
	this->roodLabel = new Label(20,30, 60, 40, backgroundLabel, "Rood", 0x000000, font);
	roodLabel->setSkin( skin );
	roodLabel->setPaddingTop(10);
	roodLabel->setPaddingLeft(12);
	this->kleurLabels.add( roodLabel );	//voeg toe aan vector

	//maak groene knop
	this->groenLabel = new Label(90,30, 60, 40, backgroundLabel, "Groen", 0x000000, font);
	groenLabel->setSkin( skin );
	groenLabel->setPaddingTop(10);
	groenLabel->setPaddingLeft(12);
	this->kleurLabels.add( groenLabel );	//voeg toe aan vector

	//maak blauwe knop
	this->blauwLabel = new Label(160,30, 60, 40, backgroundLabel, "Blauw", 0x000000, font);
	blauwLabel->setSkin( skin );
	blauwLabel->setPaddingTop(10);
	blauwLabel->setPaddingLeft(12);
	this->kleurLabels.add( blauwLabel );	//voeg toe aan vector


	//stel grootte plaatje in m.b.v. editbox
	this->editSizeBox = new EditBox(20, 80, 200, 40, backgroundLabel, "Grootte Plaatje", 0x000000, font, true, true, 256, EditBox::IM_NUMBERS);
	this->editSizeBox->setSkin(skin);
	editSizeBox->setPaddingTop(10);
	editSizeBox->setPaddingLeft(12);

	//stel naam plaatje in m.b.v. editbocx
	this->editNameBox = new EditBox(20, 130, 200, 40, backgroundLabel,  "Naam Plaatje", 0x000000, font, true, false, 256, EditBox::IM_STANDARD);
	this->editNameBox->setSkin(skin);
	editNameBox->setPaddingTop(10);
	editNameBox->setPaddingLeft(12);


	this->toepassenKnop = new Label(20, 270, 200, 40, backgroundLabel, "Toepassen", 0x000000, font);
	this->toepassenKnop->setSkin(skin);
	toepassenKnop->setPaddingTop(10);
	toepassenKnop->setPaddingLeft(12);
	this->setMain(backgroundLabel);
}

OptieScherm::~OptieScherm()
{
	//verwijder objecten van deze klasse
	delete this->getMain();
}


//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	//return achtergrond kleur
	return this->achtergrondKleur;
}


//geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	return tekst;
}

int OptieScherm::getImageGrootte() {
	return imageGrootte;
}

void OptieScherm::toepassen() {

	//Setten van de achtergrond kleur
	if(roodLabel == selectedKleurLabel) {
		this->achtergrondKleur = 0xff0000;
	}
	else if(groenLabel == selectedKleurLabel) {
		this->achtergrondKleur = 0x00ff00;
	}
	else if(blauwLabel == selectedKleurLabel) {
		this->achtergrondKleur = 0x0000ff;
	}

	//Setten van de naam
	if(this->editNameBox->getCaption() != "" && this->editNameBox->getCaption() != "Naam Plaatje") {
		this->tekst = editNameBox->getCaption(); //caption is de text in een editbox
	}

	//Setten van de grootte
	if(this->editSizeBox->getCaption() != "" && this->editSizeBox->getCaption() != "Grootte Plaatje") {
		BasicString<char> groottetekst = this->editSizeBox->getCaption();

		this->imageGrootte = Convert::toInt(groottetekst);
	}
}

void OptieScherm::show() {
	this->Screen::show();
}

void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat hoofdscherm zien
	if(keyCode == MAK_FIRE)
	{
		this->parent->show();
	}
}

void OptieScherm::pointerPressEvent(MAPoint2d point)
{

	//Point van de MApoint2d maken
	Point p;
	p.set(point.x, point.y);

	for(int i = 0; i < this->kleurLabels.size(); i++) {
		Label* label = this->kleurLabels[i];
		if(label->contains(p)) {
			//Zet de geselecteerd label op deze label
			selectedKleurLabel = label;
		}
	}

	//Als er een label geselecteerd is
	//Nodig zodat buiten de kleurlabels klikken er niet voor zorgt dat een geselecteerd gedeselecteerd word
	if(selectedKleurLabel != NULL) {
		//Set elke label zoiezo op false
		for(int i = 0; i < this->kleurLabels.size(); i++) {
			this->kleurLabels[i]->setSelected(false);
		}

		//Zet de geselecteerde label op true
		selectedKleurLabel->setSelected(true);
	}

	//behandel de editbox bij selecteren (touch)
	if(this->editNameBox->contains(p)) {
		this->editNameBox->setText("");
		this->editNameBox->setSelected(true);
	}
	else {
		this->editNameBox->setSelected(false);
	}

	//behandel de editbox bij selecteren (touch)
	if(this->editSizeBox->contains(p)) {
		this->editSizeBox->setText("");
		this->editSizeBox->setSelected(true);
	}
	else {
		this->editSizeBox->setSelected(false);
	}

	if(this->toepassenKnop->contains(p)){
		this->toepassen();
		this->parent->show();
	}
}

