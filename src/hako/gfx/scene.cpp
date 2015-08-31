#include <hako/gfx/scene.h>


Hako::Gfx::SceneNode Hako::Gfx::SceneNode::make(Kind kind)
{
	SceneNode node;
	node.active = true;
	node.dirty  = true;
	node.kind   = kind;
	return node;
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add_renderer(Hako::Gfx::Scene::Reference* parent)
{
	auto node_refer = this->add(parent, SceneNode::make(SceneNode::Kind::Renderer));

	Hako::Gfx::SceneRenderer renderer;
	renderer.active         = true;
	renderer.tree_reference = node_refer;
	renderer.mesh           = nullptr;
	renderer.material       = nullptr;
	renderer.properties     = nullptr;
	renderer.layer          = 0;
	renderer.mask           = 0;

	this->tree[node_refer].data.renderer.renderer_reference = this->renderers.add(renderer);

	return node_refer;
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add_translation(Hako::Gfx::Scene::Reference* parent)
{
	return this->add(parent, SceneNode::make(SceneNode::Kind::Translation));
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add_rotation(Hako::Gfx::Scene::Reference* parent)
{
	return this->add(parent, SceneNode::make(SceneNode::Kind::Rotation));
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add_scaling(Hako::Gfx::Scene::Reference* parent)
{
	return this->add(parent, SceneNode::make(SceneNode::Kind::Scaling));
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add_custom_transform(Hako::Gfx::Scene::Reference* parent)
{
	return this->add(parent, SceneNode::make(SceneNode::Kind::CustomTransform));
}


void Hako::Gfx::Scene::set_active(Hako::Gfx::Scene::Reference* refer, bool active)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	node->active = active;
	node->dirty  = true;
	if (node->kind == Hako::Gfx::SceneNode::Kind::Renderer)
	{
		Hako::Gfx::SceneRenderer* renderer = &this->renderers[node->data.renderer.renderer_reference];
		renderer->active = active;
	}
}


void Hako::Gfx::Scene::set_renderer_mesh(Hako::Gfx::Scene::Reference* refer, Hako::Gfx::Mesh* mesh, Hako::Gfx::Material* material, Hako::Gfx::MaterialProperties* properties)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Renderer, "scene node is not a renderer node");
	Hako::Gfx::SceneRenderer* renderer = &this->renderers[node->data.renderer.renderer_reference];
	renderer->mesh       = mesh;
	renderer->material   = material;
	renderer->properties = properties;
	node->dirty = true;
}


void Hako::Gfx::Scene::set_renderer_options(Hako::Gfx::Scene::Reference* refer, int layer, unsigned int mask)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Renderer, "scene node is not a renderer node");
	Hako::Gfx::SceneRenderer* renderer = &this->renderers[node->data.renderer.renderer_reference];
	renderer->layer = layer;
	renderer->mask  = mask;
	node->dirty = true;
}


void Hako::Gfx::Scene::set_translation(Hako::Gfx::Scene::Reference* refer, Hako::Math::Vector3 position)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Translation, "scene node is not a translation node");
	node->data.translation.position      = position;
	node->data.translation.position_last = position;
	node->dirty = true;
}


void Hako::Gfx::Scene::lerp_translation(Hako::Gfx::Scene::Reference* refer, Hako::Math::Vector3 position)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Translation, "scene node is not a translation node");
	node->data.translation.position = position;
	node->dirty = true;
}


void Hako::Gfx::Scene::set_rotation(Hako::Gfx::Scene::Reference* refer, Hako::Math::Vector3 axis, float angle)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Rotation, "scene node is not a rotation node");
	node->data.rotation.axis       = axis;
	node->data.rotation.axis_last  = axis;
	node->data.rotation.angle      = angle;
	node->data.rotation.angle_last = angle;
	node->dirty = true;
}


void Hako::Gfx::Scene::lerp_rotation(Hako::Gfx::Scene::Reference* refer, Hako::Math::Vector3 axis, float angle)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Rotation, "scene node is not a rotation node");
	node->data.rotation.axis  = axis;
	node->data.rotation.angle = angle;
	node->dirty = true;
}


void Hako::Gfx::Scene::set_scaling(Hako::Gfx::Scene::Reference* refer, Hako::Math::Vector3 scale)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Scaling, "scene node is not a scaling node");
	node->data.scaling.scale      = scale;
	node->data.scaling.scale_last = scale;
	node->dirty = true;
}


void Hako::Gfx::Scene::lerp_scaling(Hako::Gfx::Scene::Reference* refer, Hako::Math::Vector3 scale)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::Scaling, "scene node is not a scaling node");
	node->data.scaling.scale = scale;
	node->dirty = true;
}


void Hako::Gfx::Scene::set_custom_transform(Hako::Gfx::Scene::Reference* refer, Hako::Math::Matrix4 matrix)
{
	Hako::Gfx::SceneNode* node = &this->tree[*refer];
	HAKO_ASSERT(node->kind == SceneNode::Kind::CustomTransform, "scene node is not a custom transform node");
	node->data.custom_transform.matrix = matrix;
	node->dirty = true;
}


Hako::Gfx::Scene::Scene()
{

}


void Hako::Gfx::Scene::init()
{
	this->tree      .init();
	this->renderers .init();
}


Hako::Gfx::Scene::Reference Hako::Gfx::Scene::add(Reference* parent, SceneNode node)
{
	Hako::Gfx::Scene::Reference node_refer;
	if (parent == nullptr)
		node_refer = this->tree.add(node);
	else
		node_refer = this->tree.add_child(*parent, node);

	return node_refer;
}


void Hako::Gfx::Scene::advance_interpolation_frame()
{
	for (unsigned int i = 0; i < this->tree.count(); i++)
	{
		Hako::Gfx::SceneNode& node = this->tree.get_by_index(i);
        node.dirty = false;

		switch (node.kind)
		{
			case Hako::Gfx::SceneNode::Kind::Translation:
			{
				node.data.translation.position_last = node.data.translation.position;
				break;
			}
			case Hako::Gfx::SceneNode::Kind::Rotation:
			{
				node.data.rotation.axis_last  = node.data.rotation.axis;
				node.data.rotation.angle_last = node.data.rotation.angle;
				break;
			}
			default:
				break;
		}
	}
}


void Hako::Gfx::Scene::refresh_matrices(float interpolation)
{
	unsigned int node_index = 0;
	while (node_index < this->tree.count())
	{
		node_index = this->refresh_matrices_recursive(
			interpolation,
			node_index,
			Hako::Math::Matrix4::make_identity(),
			false);
	}
}


unsigned int Hako::Gfx::Scene::refresh_matrices_recursive(
	float               interpolation,
	unsigned int        node_index,
	Hako::Math::Matrix4 cur_matrix,
	bool                dirty)
{
    Hako::Gfx::SceneNode& node = this->tree.get_by_index(node_index);

    dirty = (dirty || node.dirty);

	switch (node.kind)
	{
		case Hako::Gfx::SceneNode::Kind::Renderer:
		{
		    if (dirty)
            {
                Hako::Gfx::SceneRenderer& renderer = this->renderers[node.data.renderer.renderer_reference];
                renderer.transform_matrix = cur_matrix;
            }
            break;
		}
		case Hako::Gfx::SceneNode::Kind::Translation:
		{
			cur_matrix *= Hako::Math::Matrix4::make_translation(
				Hako::Math::lerp3(node.data.translation.position_last, node.data.translation.position, interpolation));
			break;
		}
		case Hako::Gfx::SceneNode::Kind::Rotation:
		{
			cur_matrix *= Hako::Math::Matrix4::make_rotation(
				Hako::Math::slerp(node.data.rotation.axis_last, node.data.rotation.axis, interpolation),
				Hako::Math::lerp(node.data.rotation.angle_last, node.data.rotation.angle, interpolation));
			break;
		}
		default:
		{
			HAKO_WARNING("unimplemented");
			break;
		}
	}

	unsigned int next_child_index = node_index + 1;
	unsigned int child_count      = 0;
	while (child_count < this->tree.get_child_num_by_index(node_index))
	{
		next_child_index = this->refresh_matrices_recursive(
			interpolation,
			next_child_index,
			cur_matrix,
			dirty);
		child_count += 1;
	}
    return next_child_index;
}
