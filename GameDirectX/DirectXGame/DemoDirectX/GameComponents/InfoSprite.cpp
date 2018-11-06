#include "InfoSprite.h"
#include "../MapReader/tinyxml.h"

InfoSprite::InfoSprite(const char* FilePath)
{
	ReadXML(FilePath);
}

float InfoSprite::GetWidth() const
{
	return _Width;
}

float InfoSprite::GetHeight() const
{
	return _Height;
}

float InfoSprite::GetFrameWidth() const
{
	return _FrameWidth;
}

float InfoSprite::GetFrameHeight() const
{
	return _FrameHeight;
}

void InfoSprite::ReadXML(const char* FilePath)
{//Lấy tài liệu xml
	TiXmlDocument doc(FilePath);

	if (!doc.LoadFile())
	{
		MessageBox(nullptr, "Can't load Sprite xml file", "Error", MB_OK);
		return;
	}

	//Lấy thông tin thẻ
	auto sprite = doc.RootElement();

	//Lấy thông tin kích thước sprite
	sprite->QueryFloatAttribute("width", &this->_Width);
	sprite->QueryFloatAttribute("height", &this->_Height);

	//Lấy kích thích frame mặc định
	sprite->QueryFloatAttribute("framew", &this->_FrameWidth);
	sprite->QueryFloatAttribute("frameh", &this->_FrameHeight);

	//Lấy thông tin từng index
	sprite->QueryIntAttribute("frame", &this->_Frame);
	int n;
	int i = 0;
	for (auto indexXML = sprite->FirstChildElement(); indexXML != nullptr;
		indexXML = indexXML->NextSiblingElement())
	{
		_InfoFrame = new InfoFrame[i + 1];
		_Info.push_back(_InfoFrame);
		auto query = indexXML->QueryIntAttribute("n", &n);
		indexXML->QueryFloatAttribute("x", &this->_Info.at(n)->x);
		indexXML->QueryFloatAttribute("y", &this->_Info.at(n)->y);
		indexXML->QueryFloatAttribute("w", &this->_Info.at(n)->w);
		indexXML->QueryFloatAttribute("h", &this->_Info.at(n)->h);
		indexXML->QueryFloatAttribute("pX", &this->_Info.at(n)->pX);
		indexXML->QueryFloatAttribute("pY", &this->_Info.at(n)->pY);
		indexXML->QueryFloatAttribute("sX", &this->_Info.at(n)->sX);
		indexXML->QueryFloatAttribute("sY", &this->_Info.at(n)->sY);
		i++;
	}
}

RECT InfoSprite::GetRect(int Index) const
{
	RECT rect;
	rect.left = _Info.at(Index)->x;	//x = IndexInfo[Index][0];
	rect.top = _Info.at(Index)->y;		//y = IndexInfo[Index][1];
	rect.right = rect.left + _Info.at(Index)->w;
	rect.bottom = rect.top + _Info.at(Index)->h;
	return rect;
}

D3DXVECTOR2 InfoSprite::GetOrigin(int Index) const
{
	return { _Info.at(Index)->pX, _Info.at(Index)->pY };
}
