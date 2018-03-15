#include "shapevisitor.h"


ShapeVisitor::ShapeVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode)
	: BaseVisitor(pParentTreeItem, pParentNode)
{

}

void ShapeVisitor::apply( osg::Shape& pShape )
{
	if ( osg::Box* shape = dynamic_cast<osg::Box*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::Capsule* shape = dynamic_cast<osg::Capsule*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::CompositeShape* shape = dynamic_cast<osg::CompositeShape*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::Cone* shape = dynamic_cast<osg::Cone*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::Cylinder* shape = dynamic_cast<osg::Cylinder*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::HeightField* shape = dynamic_cast<osg::HeightField*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::InfinitePlane* shape = dynamic_cast<osg::InfinitePlane*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::Sphere* shape = dynamic_cast<osg::Sphere*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::TriangleMesh* shape = dynamic_cast<osg::TriangleMesh*>(&pShape) )
	{
		anaylse(*shape);
	}
	else if ( osg::ConvexHull* shape = dynamic_cast<osg::ConvexHull*>(&pShape) )
	{
		anaylse(*shape);
	}
	else
	{
		anaylse(pShape);
	}
}

void ShapeVisitor::anaylse( osg::Shape & )
{

}

void ShapeVisitor::anaylse( osg::Box &pShape )
{
    insertItem(new BinaryUpdateFunctor<void, osg::Box, const osg::Vec3&, const osg::Vec3&>(&pShape, &osg::Box::set, "set", "center", "osg::Vec3", "halfLengths", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Box, const osg::Vec3&>(&pShape, &osg::Box::setCenter, "setCenter", "center", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Box, const osg::Vec3&>(&pShape, &osg::Box::setHalfLengths, "setHalfLengths", "halfLengths", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Box, const osg::Quat&>(&pShape, &osg::Box::setRotation, "setRotation", "rotation", "osg::Quat"));
	
	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::Capsule &pShape )
{
    insertItem(new TernaryUpdateFunctor<void, osg::Capsule, const osg::Vec3&, float, float>(&pShape, &osg::Capsule::set, "set", "center", "osg::Vec3", "radius", "float", "height", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Capsule, const osg::Vec3&>(&pShape, &osg::Capsule::setCenter, "setCenter", "center", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Capsule, float>(&pShape, &osg::Capsule::setRadius, "setRadius", "radius", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Capsule, float>(&pShape, &osg::Capsule::setHeight, "setHeight", "height", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Capsule, const osg::Quat&>(&pShape, &osg::Capsule::setRotation, "setRotation", "rotation", "osg::Quat"));

	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::CompositeShape &pShape )
{
	osg::Shape* shape = pShape.getShape();
	if ( shape )
	{
		QTreeWidgetItem* treeItem = insertItem( shape );
		ShapeVisitor shapeVisitor(treeItem, mParentNode);
		shapeVisitor.apply(*shape);
	}

	for (unsigned int i = 0; i < pShape.getNumChildren(); ++i)
	{
		shape = pShape.getChild(i);
		QTreeWidgetItem* treeItem = insertItem( shape );
		ShapeVisitor shapeVisitor(treeItem, mParentNode);
		shapeVisitor.apply(*shape);
	}	
	
	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::Cone &pShape )
{
    insertItem(new TernaryUpdateFunctor<void, osg::Cone, const osg::Vec3&, float, float>(&pShape, &osg::Cone::set, "set", "center", "osg::Vec3", "radius", "float", "height", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cone, const osg::Vec3&>(&pShape, &osg::Cone::setCenter, "setCenter", "center", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cone, float>(&pShape, &osg::Cone::setRadius, "setRadius", "radius", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cone, float>(&pShape, &osg::Cone::setHeight, "setHeight", "height", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cone, const osg::Quat&>(&pShape, &osg::Cone::setRotation, "setRotation", "rotation", "osg::Quat"));
	
	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::Cylinder &pShape )
{
    insertItem(new TernaryUpdateFunctor<void, osg::Cylinder, const osg::Vec3&, float, float>(&pShape, &osg::Cylinder::set, "set", "center", "osg::Vec3", "radius", "float", "height", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cylinder, const osg::Vec3&>(&pShape, &osg::Cylinder::setCenter, "setCenter", "center", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cylinder, float>(&pShape, &osg::Cylinder::setRadius, "setRadius", "radius", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cylinder, float>(&pShape, &osg::Cylinder::setHeight, "setHeight", "height", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Cylinder, const osg::Quat&>(&pShape, &osg::Cylinder::setRotation, "setRotation", "rotation", "osg::Quat"));

	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::HeightField &pShape )
{
    // TODO set fonksiyonu yok ne yapcaz?
	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::InfinitePlane &pShape )
{
    // TODO ornek yok
	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::Sphere &pShape )
{
    insertItem(new BinaryUpdateFunctor<void, osg::Sphere, const osg::Vec3&, float>(&pShape, &osg::Sphere::set, "set", "center", "osg::Vec3", "radius", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::Sphere, const osg::Vec3&>(&pShape, &osg::Sphere::setCenter, "setCenter", "center", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osg::Sphere, float>(&pShape, &osg::Sphere::setRadius, "setRadius", "radius", "float"));

	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::TriangleMesh &pShape )
{
    // TODO Dosyaya TriangleMesh yazilmyor
    insertItem(new UnaryUpdateFunctor<void, osg::TriangleMesh, osg::Vec3Array*>(&pShape, &osg::TriangleMesh::setVertices, "setVertices", "vertices", "osg::Vec3Array"));
    insertItem(new UnaryUpdateFunctor<void, osg::TriangleMesh, osg::IndexArray*>(&pShape, &osg::TriangleMesh::setIndices, "setIndices", "indices", "osg::IndexArray"));

	anaylse( static_cast<osg::Shape&>(pShape) );
}

void ShapeVisitor::anaylse( osg::ConvexHull &pShape )
{
	anaylse( static_cast<osg::TriangleMesh&>(pShape) );
}

