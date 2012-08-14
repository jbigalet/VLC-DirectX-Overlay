#pragma once

#include <d3d9.h>
#include "../GUI_Engine/GUI_Engine.h"

class CItem_FPS : public CItem_Text {
public:
	CItem_FPS();
	void onUpdate();
};

class CItem_Filename : public CItem_Text {
public:
	CItem_Filename();
	void onUpdate();
};

class CItem_Position : public CItem_Text {
public:
	CItem_Position();
	void onUpdate();
};

class CItem_Length : public CItem_Text {
public:
	CItem_Length();
	void onUpdate();
};


class CItem_PlayPause : public CItem_Image {
public:
	bool isPlaying;
	CItem_PlayPause();
	void onClick( tagPOINT );
	void onUpdate();
};


class CItem_Backward : public CItem_Image {
public:
	CItem_Backward();
	void onClick( tagPOINT );
};


class CItem_Forward : public CItem_Image {
public:
	CItem_Forward();
	void onClick( tagPOINT );
};


class CItem_Previous : public CItem_Image {
public:
	CItem_Previous();
	void onClick( tagPOINT );
};


class CItem_Next : public CItem_Image {
public:
	CItem_Next();
	void onClick( tagPOINT );
};


class CItem_PlaylistIcon : public CItem_Image {
public:
	CItem_PlaylistIcon();
	void onClick( tagPOINT );
};


class CItem_VolumeIcon : public CItem_Image {
public:
	CItem_VolumeIcon();
	void onClick( tagPOINT );
};


class CItem_Video : public CItem_Image {
public:
	CItem_Video();
	void onUpdate();
};

class CItem_Progress : public CItem_ProgressBar {
public:
	CItem_Progress();
	void onClick( tagPOINT );
	void updateDim();
	void onUpdate();
};

class CItem_Volume : public CItem_ProgressBar {
public:
	CItem_Volume();
	void onClick( tagPOINT );
	void onUpdate();
};

class CItem_Top : public CItem {
public:
	CItem_Top();
	void updateDim();
	void draw();
};

class CItem_Bot : public CItem {
public:
	CItem_Bot();
	void updateDim();
	void draw();
};



void VLC_Overlay_Init( LPDIRECT3DDEVICE9 );

