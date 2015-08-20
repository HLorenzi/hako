#include <hako/gfx/scene.h>


Hako::Gfx::SceneNode Hako::Gfx::SceneNode::make_render()
{
	SceneNode node;
	node.kind = SceneNode::Kind::Render;
	return node;
}


Hako::Gfx::SceneNode Hako::Gfx::SceneNode::make_translation()
{
	SceneNode node;
	node.kind = SceneNode::Kind::Translation;
	return node;
}


Hako::Gfx::SceneNode Hako::Gfx::SceneNode::make_rotation()
{
	SceneNode node;
	node.kind = SceneNode::Kind::Rotation;
	return node;
}


Hako::Gfx::SceneNode Hako::Gfx::SceneNode::make_scaling()
{
	SceneNode node;
	node.kind = SceneNode::Kind::Scaling;
	return node;
}


Hako::Gfx::SceneNode Hako::Gfx::SceneNode::make_custom_transform()
{
	SceneNode node;
	node.kind = SceneNode::Kind::CustomTransform;
	return node;
}



void Hako::Gfx::SceneNode::set_translation(Hako::Math::Vector3 position)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::Translation, "scene node is not a translation node");
	this->data.translation.position      = position;
	this->data.translation.position_last = position;
}


void Hako::Gfx::SceneNode::lerp_translation(Hako::Math::Vector3 position)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::Translation, "scene node is not a translation node");
	this->data.translation.position = position;
}


void Hako::Gfx::SceneNode::set_rotation(Hako::Math::Vector3 axis, float angle)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::Rotation, "scene node is not a rotation node");
	this->data.rotation.axis       = axis;
	this->data.rotation.axis_last  = axis;
	this->data.rotation.angle      = angle;
	this->data.rotation.angle_last = angle;
}


void Hako::Gfx::SceneNode::lerp_rotation(Hako::Math::Vector3 axis, float angle)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::Rotation, "scene node is not a rotation node");
	this->data.rotation.axis  = axis;
	this->data.rotation.angle = angle;
}


void Hako::Gfx::SceneNode::set_scaling(Hako::Math::Vector3 scale)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::Scaling, "scene node is not a scaling node");
	this->data.scaling.scale      = scale;
	this->data.scaling.scale_last = scale;
}


void Hako::Gfx::SceneNode::lerp_scaling(Hako::Math::Vector3 scale)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::Scaling, "scene node is not a scaling node");
	this->data.scaling.scale = scale;
}


void Hako::Gfx::SceneNode::set_custom_transform(Hako::Math::Matrix4 matrix)
{
	HAKO_ASSERT(this->kind == SceneNode::Kind::CustomTransform, "scene node is not a custom transform node");
	this->data.custom_transform.matrix = matrix;
}


Hako::Gfx::Scene::Scene()
{

}


void Hako::Gfx::Scene::init()
{
	this->tree.init();
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add(SceneNode node)
{
	return this->tree.add(node);
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add_child(Reference& parent, SceneNode node)
{
	return this->tree.add_child(parent, node);
}
