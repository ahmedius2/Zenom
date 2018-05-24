#include "drawablevisitor.h"
#include "shapevisitor.h"

DrawableVisitor::DrawableVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode)
	: BaseVisitor(pParentTreeItem, pParentNode)
{

}

DrawableVisitor::~DrawableVisitor()
{

}

void DrawableVisitor::transverse( osg::Drawable* pDrawable )
{
	if ( osg::ShapeDrawable* shapeDrawable = dynamic_cast<osg::ShapeDrawable*>(pDrawable) )
	{
		anaylse(*shapeDrawable);
	}
	else if ( osg::Geometry* geometry = dynamic_cast<osg::Geometry*>(pDrawable) )
	{
		anaylse(*geometry);
	}
	else
	{
		anaylse(*pDrawable);
	}
}

void DrawableVisitor::anaylse( osg::Drawable &pDrawable )
{
	analyseStateSet( pDrawable.getStateSet(), *mParentNode );
}

void DrawableVisitor::anaylse( osg::ShapeDrawable &pDrawable )
{
    pDrawable.setUseDisplayList(false);	// using a display list is inefficient, because in every frame it is created and destroyed.
    insertItem(new UnaryUpdateFunctor<void, osg::ShapeDrawable, const osg::Vec4&>(&pDrawable, &osg::ShapeDrawable::setColor, "setColor", "color", "osg::Vec4"));
	
	osg::Shape* shape = pDrawable.getShape();	
	if( shape )
	{
		QTreeWidgetItem* treeItem = insertItem( shape );
		ShapeVisitor shapeVisitor(treeItem, mParentNode);
		shapeVisitor.apply(*shape);
	}
	anaylse(static_cast<osg::Drawable&>(pDrawable) );
}

void DrawableVisitor::anaylse( osg::Geometry &pDrawable )
{
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Array*, osg::Vec3Array*>(&pDrawable, &osg::Geometry::setVertexArray, "setVertexArray", "array", "osg::Vec3Array"));
    //    void 	setVertexData (const ArrayData &arrayData)
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Geometry::AttributeBinding>(&pDrawable, &osg::Geometry::setNormalBinding, "setNormalBinding", "ab", "osg::Geometry::AttributeBinding"));
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Array*, osg::Vec3Array*>(&pDrawable, &osg::Geometry::setNormalArray, "setNormalArray", "array", "osg::Vec3Array"));
    //    void 	setNormalData (const ArrayData &arrayData)
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Geometry::AttributeBinding>(&pDrawable, &osg::Geometry::setColorBinding, "setColorBinding", "ab", "osg::Geometry::AttributeBinding"));
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Array*, osg::Vec4Array*>(&pDrawable, &osg::Geometry::setColorArray, "setColorArray", "array", "osg::Vec4Array"));
    //    void 	setColorData (const ArrayData &arrayData)
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Geometry::AttributeBinding>(&pDrawable, &osg::Geometry::setSecondaryColorBinding, "setSecondaryColorBinding", "ab", "osg::Geometry::AttributeBinding"));
    insertItem(new UnaryUpdateFunctor<void, osg::Geometry, osg::Array*, osg::Vec4Array*>(&pDrawable, &osg::Geometry::setSecondaryColorArray, "setSecondaryColorArray", "array", "osg::Vec4Array"));
    //    void 	setSecondaryColorData (const ArrayData &arrayData)

    //insertItem(new UnaryUpdateFunctor<osg::Geometry, osg::Geometry::AttributeBinding>(&pDrawable, &osg::Geometry::setFogCoordBinding, "setFogCoordBinding", "ab"));
    // float ? insertItem(new UnaryUpdateFunctor<osg::Geometry, osg::Array*, osg::Vec3Array*>(&pDrawable, &osg::Geometry::setFogCoordArray, "setFogCoordArray", "array"));
    //    void 	setFogCoordData (const ArrayData &arrayData)
    //    void 	setTexCoordArray (unsigned int unit, Array *)
    //    void 	setTexCoordData (unsigned int index, const ArrayData &arrayData)
    //    void 	setVertexAttribArray (unsigned int index, Array *array)
    //    void 	setVertexAttribBinding (unsigned int index, AttributeBinding ab)
    //    void 	setVertexAttribNormalize (unsigned int index, GLboolean norm)
    //    void 	setVertexAttribData (unsigned int index, const ArrayData &arrayData)
    //    void 	setPrimitiveSetList (const PrimitiveSetList &primitives)
    //    PrimitiveSetList & 	getPrimitiveSetList ()
    //    unsigned int 	getNumPrimitiveSets () const
    //    bool 	removePrimitiveSet (unsigned int i, unsigned int numElementsToRemove=1)
    //    void 	setVertexIndices (IndexArray *array)   deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    void 	setNormalIndices (IndexArray *array)        deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    void 	setColorIndices (IndexArray *array)        deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    void 	setSecondaryColorIndices (IndexArray *array)        deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    void 	setFogCoordIndices (IndexArray *array)        deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    void 	setTexCoordIndices (unsigned int unit, IndexArray *)        deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    void 	setVertexAttribIndices (unsigned int index, IndexArray *array)        deprecated - forces OpenGL slow path, just kept for backwards compatibility.
    //    virtual void 	setUseVertexBufferObjects (bool flag)
}
