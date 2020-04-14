#include "Others/PacoConversions.h"

#include "Others/General.h"

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "OgreMatrix3.h"

#include <btBulletCollisionCommon.h>
#include <fmod.h>


// Vectors
Ogre::Vector3 PacoToOgre(const Vector3 &vector)
{
	return Ogre::Vector3(vector.X, vector.Y, vector.Z);
}

Vector3 OgreToPaco(const Ogre::Vector3 &vector)
{
	return Vector3(vector.x, vector.y, vector.z);
}

btVector3 PacoToBullet(const Vector3& vector) {
	return btVector3(vector.X, vector.Y, vector.Z);
}

Vector3 BulletToPaco(const btVector3& vector) {
	return Vector3(vector.getX(), vector.getY(), vector.getZ());
}

FMOD_VECTOR PacoToFMOD(const Vector3& vector) {
	FMOD_VECTOR fVec;
	fVec.x = vector.X;
	fVec.y = vector.Y;
	fVec.z = vector.Z;

	return fVec;
}


// Quaternions
Ogre::Quaternion PacoToOgre(const Quaternion& quaternion) {
	return Ogre::Quaternion(quaternion.W, quaternion.X, quaternion.Y, quaternion.Z);
}

Quaternion OgreToPaco(const Ogre::Quaternion& quaternion) {
	return Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

btQuaternion PacoToBullet(const Quaternion& quaternion)
{
	return btQuaternion(quaternion.X, quaternion.Y, quaternion.Z, quaternion.W);
}

Quaternion BulletToPaco(const btQuaternion& quaternion)
{
	return Quaternion(quaternion.getX(), quaternion.getY(), quaternion.getZ(), quaternion.getW());
}

// Type cast operator definitions

Vector3::operator Ogre::Vector3() const {
	return PacoToOgre(*this);
}

Vector3::operator btVector3() const {
	return PacoToBullet(*this);
}

Quaternion::operator Ogre::Quaternion() const {
	return PacoToOgre(*this);
}

Quaternion::operator btQuaternion() const {
	return PacoToBullet(*this);
}