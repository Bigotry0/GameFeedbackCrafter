## TransformBase
**Class Name:** UGFE_TransformBase \
**Effect Type:** BaseClass \
**Description:** Base class for transform effects. \
**Configuration:**
- `ActorSelection`: `FGFActorSelection`
	Actor selection, used to determine the target actor/component. You can specify the target actor/component directly or use the self actor/component. Self actor/component is the context actor/component of the effect.
- `TransformSpace`: `ETransformSpace`
	Transform space for the target actor/component. (World or Local)

## Location
**Class Name:** UGFE_Transform_Location \
**Effect Type:** Transform \
**Description:** Transforms the location of the target actor/component. \
**Configuration:**
- `StartLocation`: `FVector`
	Start location of the target actor/component.
- `EndLocation`: `FVector`
	End location of the target actor/component.

## Rotation
**Class Name:** UGFE_Transform_Rotation \
**Effect Type:** Transform \
**Description:** Transforms the rotation of the target actor/component. \
**Configuration:**
- `RotateMode`: `ERotateMode`
	Rotation mode for the target actor/component \
	Absolute: Set the rotation directly \
	Additive: Add the rotation to the current rotation \
	ToTarget: Rotate to the target rotation \
- `StartRotation`: `FRotator`
	Start rotation of the target actor/component.
- `EndRotation`: `FRotator`
	End rotation of the target actor/component.
- `bUseQuatLerp`: `bool`
	Use quaternion lerp instead of euler lerp.
- `RotateLerpMode`: `ERotateLerpMode`
	Lerp mode for quaternion lerp.

## Scale
**Class Name:** UGFE_Transform_Scale \
**Effect Type:** Transform \
**Description:** Transforms the scale of the target actor/component. \
**Configuration:**
- `StartScale`: `FVector`
	Start scale of the target actor/component.
- `EndScale`: `FVector`
	End scale of the target actor/component.

