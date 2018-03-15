#include "transformvisitor.h"


TransformVisitor::TransformVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode)
	: BaseVisitor(pParentTreeItem, pParentNode)
{

}

void TransformVisitor::transverse(osg::Transform* pTransform)
{
	if ( osg::AutoTransform* transform = dynamic_cast<osg::AutoTransform*>(pTransform) )
	{
		anaylse(*transform);
	}
	else if ( osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(pTransform) )
	{
		anaylse(*transform);
	}
	else if ( osg::PositionAttitudeTransform* transform = dynamic_cast<osg::PositionAttitudeTransform*>(pTransform) )
	{
		anaylse(*transform);
	}
    else if ( osgAnimation::Bone* transform = dynamic_cast<osgAnimation::Bone*>(pTransform) )
    {
        anaylse(*transform);
    }
    else if ( osgSim::DOFTransform* transform = dynamic_cast<osgSim::DOFTransform*>(pTransform) )
    {
        anaylse(*transform);
    }
	else
	{
		anaylse(*pTransform);
	}
}

void TransformVisitor::anaylse( osg::Transform & )
{

}

void TransformVisitor::anaylse( osg::AutoTransform &pTransform )
{
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, const osg::Vec3d&>(&pTransform, &osg::AutoTransform::setPosition, "setPosition", "pos", "osg::Vec3d"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, const osg::Quat&>(&pTransform, &osg::AutoTransform::setRotation, "setRotation", "rotation", "osg::Quat"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, double>(&pTransform, &osg::AutoTransform::setScale, "setScale", "scale", "double"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, const osg::Vec3d&>(&pTransform, &osg::AutoTransform::setScale, "setScale", "scale", "osg::Vec3d"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, double>(&pTransform, &osg::AutoTransform::setMinimumScale, "setMinimumScale", "minimumScale", "double"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, double>(&pTransform, &osg::AutoTransform::setMaximumScale, "setMaximumScale", "maximumScale", "double"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, const osg::Vec3d&>(&pTransform, &osg::AutoTransform::setPivotPoint, "setPivotPoint", "pivot", "osg::Vec3d"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, float>(&pTransform, &osg::AutoTransform::setAutoUpdateEyeMovementTolerance, "setAutoUpdateEyeMovementTolerance", "tolerance", "float"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, osg::AutoTransform::AutoRotateMode>(&pTransform, &osg::AutoTransform::setAutoRotateMode, "setAutoRotateMode", "mode", "osg::AutoTransform::AutoRotateMode"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, bool>(&pTransform, &osg::AutoTransform::setAutoScaleToScreen, "setAutoScaleToScreen", "autoScaleToScreen", "bool"));
    insertItem(new UnaryUpdateFunctor<void, osg::AutoTransform, float>(&pTransform, &osg::AutoTransform::setAutoScaleTransitionWidthRatio, "setAutoScaleTransitionWidthRatio", "ratio", "float"));

	anaylse(static_cast<osg::Transform&>(pTransform) );
}

void TransformVisitor::anaylse( osg::MatrixTransform &pTransform )
{
    insertItem(new UnaryUpdateFunctor<void, osg::MatrixTransform, const osg::Matrix&>(&pTransform, &osg::MatrixTransform::setMatrix, "setMatrix", "matrix", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osg::MatrixTransform, const osg::Matrix&>(&pTransform, &osg::MatrixTransform::preMult, "preMult", "matrix", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osg::MatrixTransform, const osg::Matrix&>(&pTransform, &osg::MatrixTransform::postMult, "postMult", "matrix", "osg::Matrix"));

	anaylse(static_cast<osg::Transform&>(pTransform) );
}

void TransformVisitor::anaylse( osg::PositionAttitudeTransform &pTransform )
{
    insertItem(new UnaryUpdateFunctor<void, osg::PositionAttitudeTransform, const osg::Vec3d&>(&pTransform, &osg::PositionAttitudeTransform::setPosition, "setPosition", "position", "osg::Vec3d"));
    insertItem(new UnaryUpdateFunctor<void, osg::PositionAttitudeTransform, const osg::Quat&>(&pTransform, &osg::PositionAttitudeTransform::setAttitude, "setAttitude", "attitude", "osg::Quat"));
    insertItem(new UnaryUpdateFunctor<void, osg::PositionAttitudeTransform, const osg::Vec3d&>(&pTransform, &osg::PositionAttitudeTransform::setScale, "setScale", "scale", "osg::Vec3d"));
    insertItem(new UnaryUpdateFunctor<void, osg::PositionAttitudeTransform, const osg::Vec3d&>(&pTransform, &osg::PositionAttitudeTransform::setPivotPoint, "setPivotPoint", "pivot", "osg::Vec3d"));

	anaylse(static_cast<osg::Transform&>(pTransform) );
}

void TransformVisitor::analyse(osgAnimation::Bone &pTransform)
{
    insertItem(new UnaryUpdateFunctor<void, osgAnimation::Bone, const osg::Matrix&>(&pTransform, &osgAnimation::Bone::setMatrixInSkeletonSpace, "setMatrixInSkeletonSpace", "matrix", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osgAnimation::Bone, const osg::Matrix&>(&pTransform, &osgAnimation::Bone::setInvBindMatrixInSkeletonSpace, "setInvBindMatrixInSkeletonSpace", "matrix", "osg::Matrix"));

    anaylse(static_cast<osg::Transform&>(pTransform) );
}

void TransformVisitor::analyse(osgSim::DOFTransform &pTransform)
{
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMinHPR, "setMinHPR", "hpr", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMaxHPR, "setMaxHPR", "hpr", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setIncrementHPR, "setIncrementHPR", "hpr", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setCurrentHPR, "setCurrentHPR", "hpr", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::updateCurrentHPR, "updateCurrentHPR", "hpr", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMinTranslate, "setMinTranslate", "translate", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMaxTranslate, "setMaxTranslate", "translate", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setIncrementTranslate, "setIncrementTranslate", "translate", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setCurrentTranslate, "setCurrentTranslate", "translate", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::updateCurrentTranslate, "updateCurrentTranslate", "translate", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMinScale, "setMinScale", "scale", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMaxScale, "setMaxScale", "scale", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setIncrementScale, "setIncrementScale", "scale", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setCurrentScale, "setCurrentScale", "scale", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::updateCurrentScale, "updateCurrentScale", "scale", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Vec3&>(&pTransform, &osgSim::DOFTransform::setMinScale, "setMinScale", "scale", "osg::Vec3"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Matrix&>(&pTransform, &osgSim::DOFTransform::setPutMatrix, "setPutMatrix", "put", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, const osg::Matrix&>(&pTransform, &osgSim::DOFTransform::setInversePutMatrix, "setInversePutMatrix", "inversePut", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, osgSim::DOFTransform::MultOrder>(&pTransform, &osgSim::DOFTransform::setHPRMultOrder, "setHPRMultOrder", "order", "osgSim::DOFTransform::MultOrder"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, bool>(&pTransform, &osgSim::DOFTransform::setAnimationOn, "setAnimationOn", "do_animate", "bool"));
    insertItem(new UnaryUpdateFunctor<void, osgSim::DOFTransform, float>(&pTransform, &osgSim::DOFTransform::animate, "animate", "deltaTime", "float"));

    anaylse(static_cast<osg::Transform&>(pTransform) );
}
