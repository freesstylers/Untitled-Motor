#pragma once

// Ogre
namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<2, Real> Vector2;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
	class Matrix3;

	class Node;
	class SceneNode;
};

enum TransformSpace
{
    /// Transform is relative to the local space
    LOCAL,
    /// Transform is relative to the space of the parent node
    PARENT,
    /// Transform is relative to world space
    WORLD
};

// Bullet
class btVector3;
class btQuaternion;
class btMatrix3x3;

// FMOD
struct FMOD_VECTOR;

// Paco
struct Vector2;
struct Vector3;
struct Quaternion;
struct Matrix3x3;


// CONVERSION FUNCTIONS
// Vectors
Ogre::Vector3 PacoToOgre(const Vector3& vector);
Vector3 OgreToPaco(const Ogre::Vector3& vector);
btVector3 PacoToBullet(const Vector3& vector);
Vector3 BulletToPaco(const btVector3& vector);
FMOD_VECTOR PacoToFMOD(const Vector3& vector);

// Quaternions
Ogre::Quaternion PacoToOgre(const Quaternion& quaternion);
Quaternion OgreToPaco(const Ogre::Quaternion& quaternion);
btQuaternion PacoToBullet(const Quaternion& quaternion);
Quaternion BulletToPaco(const btQuaternion& quaternion);