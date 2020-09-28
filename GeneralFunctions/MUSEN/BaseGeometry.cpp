/* Copyright (c) 2013-2020, MUSEN Development Team. All rights reserved.
   This file is part of MUSEN framework http://msolids.net/musen.
   See LICENSE file for license and warranty information. */

#include "BaseGeometry.h"

#include "MeshGenerator.h"
#include "ProtoFunctions.h"

std::string CBaseGeometry::Name() const
{
	return m_name;
}

void CBaseGeometry::SetName(const std::string& _name)
{
	m_name = _name;
}

std::string CBaseGeometry::Key() const
{
	return m_key;
}

void CBaseGeometry::SetKey(const std::string& _key)
{
	m_key = _key;
}

EVolumeShape CBaseGeometry::Shape() const
{
	return m_shape;
}

void CBaseGeometry::StoreShape(const EVolumeShape& _shape)
{
	m_shape = _shape;
}

CColor CBaseGeometry::Color() const
{
	return m_color;
}

void CBaseGeometry::SetColor(const CColor& _color)
{
	m_color = _color;
}

CMatrix3 CBaseGeometry::RotationMatrix() const
{
	return m_rotation;
}

void CBaseGeometry::StoreRotationMatrix(const CMatrix3& _matrix)
{
	m_rotation = _matrix;
}

size_t CBaseGeometry::Accuracy() const
{
	return CMeshGenerator::TrianglesToAccuracy(Shape(), TrianglesNumber());
}

void CBaseGeometry::SetSizes(const CGeometrySizes& _sizes)
{
	m_sizes = _sizes;
	m_scaling = 1.0;
}

CGeometrySizes CBaseGeometry::Sizes() const
{
	return m_sizes;
}

void CBaseGeometry::Scale(double _factor)
{
	m_sizes.Scale(_factor / m_scaling);
	m_scaling = _factor;
}

void CBaseGeometry::ScaleSTL(const CVector3& _factors)
{
	if (Shape() != EVolumeShape::VOLUME_STL) return;
	m_scaling = 1.0;
}

void CBaseGeometry::Rotate(const CMatrix3& _rotation)
{
	m_rotation = _rotation * m_rotation;
}

double CBaseGeometry::ScalingFactor() const
{
	return m_scaling;
}

CGeometryMotion* CBaseGeometry::Motion()
{
	return &m_motion;
}

const CGeometryMotion* CBaseGeometry::Motion() const
{
	return &m_motion;
}

void CBaseGeometry::SaveToProto(ProtoBaseGeometry& _proto) const
{
	_proto.set_version(0);
	_proto.set_name(m_name);
	_proto.set_key(m_key);
	_proto.set_shape(E2I(m_shape));
	Val2Proto(_proto.mutable_color(), m_color);
	for (double size : m_sizes.RelevantSizes(m_shape))
		_proto.add_sizes(size);
	Val2Proto(_proto.mutable_rotation(), m_rotation);
	m_motion.SaveToProto(*_proto.mutable_motion());
	_proto.set_scaling(m_scaling);
}

void CBaseGeometry::LoadFromProto(const ProtoBaseGeometry& _proto)
{
	m_name = _proto.name();
	m_key = _proto.key();
	m_shape = static_cast<EVolumeShape>(_proto.shape());
	m_color = Proto2Val(_proto.color());
	m_sizes.SetRelevantSizes(Proto2Val<double>(_proto.sizes()), m_shape);
	m_rotation = Proto2Val(_proto.rotation());
	m_motion.LoadFromProto(_proto.motion());
	m_scaling = _proto.scaling() != 0 ? _proto.scaling() : 1.0;
}
