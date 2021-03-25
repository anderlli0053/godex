#pragma once

#include "../../components/component.h"
#include "../../storage/shared_steady_storage.h"
#include <BulletCollision/CollisionShapes/btConvexPointCloudShape.h>
#include <btBulletCollisionCommon.h>

struct BtRigidShape {
	enum ShapeType {
		TYPE_BOX,
		TYPE_SPHERE,
		TYPE_CAPSULE,
		TYPE_CONE,
		TYPE_CYLINDER,
		TYPE_WORLD_MARGIN,
		TYPE_CONVEX,
		TYPE_TRIMESH
	};

protected:
	/// This is used to know the type of the shape, so we know how to extract
	/// the shape common info, like the `btCollisionShape`.
	ShapeType type;

	/// List of bodies where this shape is assigned.
	/// TODO Do I really need this, can I take this infor from the storage instead??
	LocalVector<EntityID> bodies;

public:
	BtRigidShape(ShapeType p_type) :
			type(p_type) {}

	btCollisionShape *get_shape();
	const btCollisionShape *get_shape() const;

	void add_body(EntityID p_entity) {
		bodies.push_back(p_entity);
	}
};

struct BtShapeBox : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeBox, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btBoxShape box = btBoxShape(btVector3(1.0, 1.0, 1.0));

	BtShapeBox() :
			BtRigidShape(TYPE_BOX) {}

	void set_half_extents(const Vector3 &p_half_extends);
	Vector3 get_half_extents() const;

	void set_margin(real_t p_margin);
	real_t get_margin() const;
};

struct BtShapeSphere : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeSphere, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btSphereShape sphere = btSphereShape(1.0);

	BtShapeSphere() :
			BtRigidShape(TYPE_SPHERE) {}

	void set_radius(real_t p_radius);
	real_t get_radius() const;
};

struct BtShapeCapsule : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeCapsule, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btCapsuleShape capsule = btCapsuleShape(1.0, 1.0); // Radius, Height

	BtShapeCapsule() :
			BtRigidShape(TYPE_CAPSULE) {}

	void set_radius(real_t p_radius);
	real_t get_radius() const;

	void set_height(real_t p_height);
	real_t get_height() const;
};

struct BtShapeCone : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeCone, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btConeShape cone = btConeShape(1.0, 1.0); // Radius, Height

	BtShapeCone() :
			BtRigidShape(TYPE_CONE) {}

	void set_radius(real_t p_radius);
	real_t get_radius() const;

	void set_height(real_t p_height);
	real_t get_height() const;

	void set_margin(real_t p_margin);
	real_t get_margin() const;
};

struct BtShapeCylinder : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeCylinder, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btCylinderShape cylinder = btCylinderShape(btVector3(1.0, 1.0, 1.0)); // Half extents

	BtShapeCylinder() :
			BtRigidShape(TYPE_CYLINDER) {}

	void set_radius(real_t p_radius);
	real_t get_radius() const;

	void set_height(real_t p_height);
	real_t get_height() const;

	void set_margin(real_t p_margin);
	real_t get_margin() const;
};

struct BtShapeWorldMargin : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeWorldMargin, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btStaticPlaneShape world_margin = btStaticPlaneShape(btVector3(0, 1, 0), 0.0); // Normal, Distance

	BtShapeWorldMargin() :
			BtRigidShape(TYPE_WORLD_MARGIN) {}
};

struct BtShapeConvex : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeConvex, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	btConvexPointCloudShape convex = btConvexPointCloudShape();

	BtShapeConvex() :
			BtRigidShape(TYPE_CONVEX) {}
};

struct BtShapeTrimesh : public BtRigidShape {
	COMPONENT_CUSTOM_CONSTRUCTOR(BtShapeTrimesh, SharedSteadyStorage)

	static void _bind_methods();
	static void _get_storage_config(Dictionary &r_config);

	// TODO can we don't use a pointer here?
	btBvhTriangleMeshShape *trimesh = nullptr;

	BtShapeTrimesh() :
			BtRigidShape(TYPE_TRIMESH) {}
};