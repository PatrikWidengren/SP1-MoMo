#include "CharRand.h"
#include <cstdlib>

using namespace std;

sf::Texture textureCat;
sf::Image imageCat;
static const string filename = "Resource Files/Sprites/cat.png";
static const string cat_idle = "Resource Files/SpriteSheets/FWD_L_IDLE.png";
static const string cat_walk = "Resource Files/SpriteSheets/Meep_Idle_Pushmower1.png";
static const int spriteWidth = 64;
static const int spriteHeight = 64;

CharRand::CharRand(int arrX, int arrY, int moveLength, bool lockDir) :
	mArrayX(arrX),
	mArrayY(arrY),
	mStartPos{ arrX, arrY },
	mSpeed(moveLength),
	mDirLock(lockDir),
	mBaseType(6.0f),
	mOrigLast(2.0f){
	/*I am as of now unsure how to handle values like 
	4.1, 4.2, etc for other random NPCs. Will update code as it becomes 
	relevant*/
	mType = 6.0f;
	//dåligt tilfällig lösning. Fixa snart.
	mLast = 2.0f;


	mTextureSheet.loadFromFile(cat_idle);
	mCatIdleSheet.setTexture(mTextureSheet);
	//mTextureSheet.loadFromFile(cat_walk);
	//mCatWalkSheet.setTexture(mTextureSheet);

	//for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 8; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * 0), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "idle1";// << 1 + 1;
		catAnimator.addAnimation(tempName.str(), frame, sf::seconds(1.1f));
	//}
	catAnimator.playAnimation("idle1", true);
}

CharRand::~CharRand(){
}
void CharRand::changeAnimation(std::string name) {
	catAnimator.playAnimation(name, true);
}
void CharRand::playAnimation() {
	catAnimator.update(clock.restart());
	catAnimator.animate(mCatIdleSheet);
}
void CharRand::reset() {
	mArrayX = mStartPos[0];
	mArrayY = mStartPos[1];
	mLast = mOrigLast;
}

intVector CharRand::move(){
	intVector movement;
	if (mDirLock){
		int dir = rand()%9+1;
		for (int i = 0; i < mSpeed; i++){
			movement.push_back(dir);
		}
	}
	else {
		for (int i = 0; i < mSpeed; i++){
			movement.push_back(rand()%9+1);
		}
	}
	return movement;
}

/*This function is oddly constructed, though I didn't know a better way
to have it cycle through different moves without randomizing each move in
the map class. When NPC's collide the takeTurn function in Map will 
go into a loop and try to move them according to the intVector that was
returned. Once it has successfully taken a step, reaches the end of the
vector, or reaches a 0, it will stop trying and end the movement
for the turn for that NPC.*/
intVector CharRand::collide(intVector moves, int atPos){
	intVector movement;
	int m = moves.at(atPos);
	for (int i = 0; i < 7; i++){
		m++;
		if (m == 5){
			m++;
		}
		if (m>9){
			m = (m % 9);
		}
		movement.push_back(m);
	}
	return movement;
}

int CharRand::getX(){
	return mArrayX;
}

int CharRand::getY(){
	return mArrayY;
}

void CharRand::setX(int x){
	mArrayX = x;
}

void CharRand::setY(int y){
	mArrayY = y;
}

void CharRand::setLast(float l){
	mLast = l;
	mType = mBaseType + (mLast - 2);
}

float CharRand::getLast(){
	return mLast;
}

float CharRand::getType(){
	return mType;
}

bool CharRand::getCollide(){
	return false;
}
sf::Sprite* CharRand::getSpriteSheet(){
	return &mCatIdleSheet;
}
void CharRand::initialize(){
}

void CharRand::finalize(){
	textureCat.~Texture();
	imageCat.~Image();
}