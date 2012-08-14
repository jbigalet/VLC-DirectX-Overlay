#include "VLC_Overlay.h"
#include "utility.h"
#include "VLC_thread.h"
#include "VLC_JSON.h"

CItem_PlayPause::CItem_PlayPause() :
	CItem_Image("PlayPause","", false, true, "Bot", MIDDLEX, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_PlayPause::onClick( tagPOINT curPos ){
	this->isPlaying = !this->isPlaying;
	SENDVLC( PAUSE );
}

void CItem_PlayPause::onUpdate(){
	this->isPlaying = (VLC_Status.state == "playing");
	if( this->isPlaying )	fImage = "../images/pause.png";
	else					fImage = "../images/play.png";
}


CItem_Backward::CItem_Backward() :
	CItem_Image("Backward","../images/backward.png", false, true, "PlayPause", LEFTEXTERIOR, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_Backward::onClick( tagPOINT curPos ){
	SENDVLC_( SEEKRELN, 10 );
}


CItem_Forward::CItem_Forward() :
	CItem_Image("Forward","../images/forward.png", false, true, "PlayPause", RIGHTEXTERIOR, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_Forward::onClick( tagPOINT curPos ){
	SENDVLC_( SEEKRELP, 10 );
}


CItem_Next::CItem_Next() :
	CItem_Image("Next","../images/next.png", false, true, "Forward", RIGHTEXTERIOR, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_Next::onClick( tagPOINT curPos ){
	SENDVLC( NEXT );
}


CItem_Previous::CItem_Previous() :
	CItem_Image("Previous","../images/previous.png", false, true, "Backward", LEFTEXTERIOR, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_Previous::onClick( tagPOINT curPos ){
	SENDVLC( PREVIOUS );
}


CItem_PlaylistIcon::CItem_PlaylistIcon() :
	CItem_Image("PlaylistIcon","../images/playlist_icon.png", false, true, "Bot", LEFTINTERIOR, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_PlaylistIcon::onClick( tagPOINT curPos ){
	//SENDVLC( PREVIOUS );
}


CItem_VolumeIcon::CItem_VolumeIcon() :
	CItem_Image("VolumeIcon","../images/volume_icon.png", false, true, "Bot", RIGHTINTERIOR, 0, "Bot", BOTTOMINTERIOR, 0) {}

void CItem_VolumeIcon::onClick( tagPOINT curPos ){
	m_engine.getItem( "Volume" )->isInvisible = !m_engine.getItem( "Volume" )->isInvisible;
}


CItem_Video::CItem_Video() :
	CItem_Image("Video","", true, false, "Main", LEFTINTERIOR, 0, "Main", TOPINTERIOR, 0) {}

void CItem_Video::onUpdate(){
		// TODO: redo everything -_-
	if( GetAsyncKeyState( VK_CONTROL ) ){

		bool key[10];
		for(int i=1 ; i<=10 ; i++)
			key[i] = isKeyDown( VK_NUMPAD0+i );

			// X alignement
		if( key[1] || key[4] || key[7] )
			m_engine.getItem("Main")->posX.pos = 0;
		else if( key[2] || key[5] || key[8] )
			m_engine.getItem("Main")->posX.pos = (m_engine.getItem("Viewport")->dimX - dimX)/2;
		else if( key[3] || key[6] || key[9] )
			m_engine.getItem("Main")->posX.pos = m_engine.getItem("Viewport")->dimX - dimX;

			// Y alignement
		if( key[1] || key[2] || key[3] )
			m_engine.getItem("Main")->posY.pos = m_engine.getItem("Viewport")->dimY - (dimY + m_engine.getItem("Bot")->dimY);
		else if( key[4] || key[5] || key[6] )
			m_engine.getItem("Main")->posY.pos = (m_engine.getItem("Viewport")->dimY - (dimY + m_engine.getItem("Bot")->dimY))/2;
		else if( key[7] || key[8] || key[9] )
			m_engine.getItem("Main")->posY.pos = m_engine.getItem("Top")->dimY;


		if( isKeyPressed( VK_NUMPAD0 ) )
			m_engine.getItem("Main")->isInvisible = !m_engine.getItem("Main")->isInvisible;
	}


	if( VLC_Status.type == "Video" )
		fImage = getBLastAndRemoveFromDirectory("../show/", "*.jpg");
	else
		fImage = "../images/audio_img.png";
}



CItem_Progress::CItem_Progress() :
	CItem_ProgressBar("Progress", 0, 100, 100, 10, 0, 0, D3DCOLOR_ARGB(0,0,0,0), D3DCOLOR_ARGB(255,70,70,70), HORIZONTAL,
					  "Video", MIDDLEX, 0, "Video", BOTTOMEXTERIOR, 1) {}

void CItem_Progress::updateDim(){
	dimX = m_engine.getItem("Video")->dimX - 102;
	dimY = thickness;
}

void CItem_Progress::onUpdate(){
	if( VLC_Status.isInit ){
		minValue = 0;
		maxValue = VLC_Status.length;
		value = VLC_Status.time;
	}
}

void CItem_Progress::onClick( tagPOINT curPos ){
	SENDVLC_( SEEK, getClickedValue( curPos ) );
}


CItem_Volume::CItem_Volume() :
	CItem_ProgressBar("Volume", 0, 512, 100, 20, 3, 3, D3DCOLOR_ARGB(255,40,40,40), D3DCOLOR_ARGB(255,70,70,70), VERTICAL,
					  "Bot", RIGHTEXTERIOR, 5, "Bot", BOTTOMINTERIOR, 0) { this->isInvisible = true; }

void CItem_Volume::onUpdate(){
	if( VLC_Status.isInit )
		value = VLC_Status.volume;
}

void CItem_Volume::onClick( tagPOINT curPos ){
	SENDVLC_( VOLUME, getClickedValue( curPos ) );
}


CItem_FPS::CItem_FPS() : CItem_Text("FPS", "FPS: ?", 15, FW_BOLD, "Arial", D3DCOLOR_ARGB(255,255,255,255), 60, "Video", RIGHTINTERIOR, 0, "Video", TOPINTERIOR, 0) {}

void CItem_FPS::onUpdate(){
	text = "FPS: " + Str(getFPS());
}


CItem_Filename::CItem_Filename() : CItem_Text("Filename", "Filename?", 15, FW_BOLD, "Arial", D3DCOLOR_ARGB(255,255,255,255), 400, "Video", MIDDLEX, 0, "Video", TOPEXTERIOR, 0) {}

void CItem_Filename::onUpdate(){
	if( VLC_Status.isInit )
		text = VLC_Status.filename;
}


CItem_Position::CItem_Position() : CItem_Text("Position", "Position?", 12, FW_BOLD, "Arial", D3DCOLOR_ARGB(255,255,255,255), 75, "Video", LEFTINTERIOR, 3, "Video", BOTTOMEXTERIOR, -1) {}

void CItem_Position::onUpdate(){
	if( VLC_Status.isInit )
		text = formatTime( VLC_Status.time );
}


CItem_Length::CItem_Length() : CItem_Text("Length", "Length?", 12, FW_BOLD, "Arial", D3DCOLOR_ARGB(255,255,255,255), 75, "Video", RIGHTINTERIOR, 3, "Video", BOTTOMEXTERIOR, -1) {}

void CItem_Length::onUpdate(){
	if( VLC_Status.isInit )
		text = formatTime( VLC_Status.length );
}



CItem_Top::CItem_Top() : CItem("Top", true, false, 0, 25, "Video", MIDDLEX, 0, "Video", TOPEXTERIOR, 0){}

void CItem_Top::updateDim(){
	dimX = m_engine.getItem("Video")->dimX;
}

void CItem_Top::draw(){
	m_engine.drawHorizontalShaderedRectangle(iPosX, iPosY, dimX, dimY, D3DCOLOR_ARGB(255,73,73,73), D3DCOLOR_ARGB(255,22,22,22));
}



CItem_Bot::CItem_Bot() : CItem("Bot", true, false, 0, 46, "Video", MIDDLEX, 0, "Video", BOTTOMEXTERIOR, 0){}

void CItem_Bot::updateDim(){
	dimX = m_engine.getItem("Video")->dimX;
}

void CItem_Bot::draw(){
	m_engine.drawRectangle(iPosX, iPosY, dimX, 1, D3DCOLOR_ARGB(255,65,65,65));
	m_engine.drawRectangle(iPosX, iPosY+1, dimX, 10, D3DCOLOR_ARGB(255,41,41,41));
	m_engine.drawRectangle(iPosX, iPosY+11, dimX, 1, D3DCOLOR_ARGB(255,0,0,0));
	m_engine.drawRectangle(iPosX, iPosY+12, dimX, 1, D3DCOLOR_ARGB(255,74,74,74));
	m_engine.drawHorizontalShaderedRectangle(iPosX, iPosY+13, dimX, 33, D3DCOLOR_ARGB(255,42,42,42), D3DCOLOR_ARGB(255,25,25,25));
	m_engine.drawRectangle(iPosX+50, iPosY+1, 1, 10, D3DCOLOR_ARGB(255,0,0,0));
	//m_engine.drawRectangle(iPosX+51, iPosY+1, 1, 10, D3DCOLOR_ARGB(255,74,74,74));
	m_engine.drawRectangle(iPosX+dimX-50, iPosY+1, 1, 10, D3DCOLOR_ARGB(255,0,0,0));
}



void VLC_Overlay_Init( LPDIRECT3DDEVICE9 pDevice ){
	m_engine.initialize( pDevice );
	m_engine.addItem(new CItem_Video());

	m_engine.addItem(new CItem_Top());
	m_engine.addItem(new CItem_Bot());

	//m_engine.addItem(new CItem_FPS());
	m_engine.addItem(new CItem_Filename());
	m_engine.addItem(new CItem_Position());
	m_engine.addItem(new CItem_Length());

	m_engine.addItem(new CItem_Progress());
	m_engine.addItem(new CItem_Volume());
	m_engine.addItem(new CItem_VolumeIcon());

	m_engine.addItem(new CItem_PlayPause());
	m_engine.addItem(new CItem_Backward());
	m_engine.addItem(new CItem_Forward());
	m_engine.addItem(new CItem_Previous());
	m_engine.addItem(new CItem_Next());
	m_engine.addItem(new CItem_PlaylistIcon());
}
