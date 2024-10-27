// MIT License - Copyright (c) 2024 Lim Young

#include "Util/GFEasing.h"

const float BACK_INOUT_OVERSHOOT_MODIFIER = 1.525f;
const float BOUNCE_R = 1.0f / 2.75f;		  // reciprocal
const float BOUNCE_K1 = BOUNCE_R;			  // 36.36%
const float BOUNCE_K2 = 2 * BOUNCE_R;		  // 72.72%
const float BOUNCE_K3 = 1.5f * BOUNCE_R;	  // 54.54%
const float BOUNCE_K4 = 2.5f * BOUNCE_R;	  // 90.90%
const float BOUNCE_K5 = 2.25f * BOUNCE_R;	  // 81.81%
const float BOUNCE_K6 = 2.625f * BOUNCE_R;	  // 95.45%
const float BOUNCE_K0 = 7.5625f;

float FGFEasing::Ease(float t, EGFEaseType EaseType)
{
	switch (EaseType)
	{
		default:
		case EGFEaseType::Linear:
			return EaseLinear(t);
		case EGFEaseType::Smoothstep:
			return EaseSmoothstep(t);
		case EGFEaseType::Stepped:
			return EaseStepped(t);
		case EGFEaseType::InSine:
			return EaseInSine(t);
		case EGFEaseType::OutSine:
			return EaseOutSine(t);
		case EGFEaseType::InOutSine:
			return EaseInOutSine(t);
		case EGFEaseType::InQuad:
			return EaseInQuad(t);
		case EGFEaseType::OutQuad:
			return EaseOutQuad(t);
		case EGFEaseType::InOutQuad:
			return EaseInOutQuad(t);
		case EGFEaseType::InCubic:
			return EaseInCubic(t);
		case EGFEaseType::OutCubic:
			return EaseOutCubic(t);
		case EGFEaseType::InOutCubic:
			return EaseInOutCubic(t);
		case EGFEaseType::InQuart:
			return EaseInQuart(t);
		case EGFEaseType::OutQuart:
			return EaseOutQuart(t);
		case EGFEaseType::InOutQuart:
			return EaseInOutQuart(t);
		case EGFEaseType::InQuint:
			return EaseInQuint(t);
		case EGFEaseType::OutQuint:
			return EaseOutQuint(t);
		case EGFEaseType::InOutQuint:
			return EaseInOutQuint(t);
		case EGFEaseType::InExpo:
			return EaseInExpo(t);
		case EGFEaseType::OutExpo:
			return EaseOutExpo(t);
		case EGFEaseType::InOutExpo:
			return EaseInOutExpo(t);
		case EGFEaseType::InCirc:
			return EaseInCirc(t);
		case EGFEaseType::OutCirc:
			return EaseOutCirc(t);
		case EGFEaseType::InOutCirc:
			return EaseInOutCirc(t);
		case EGFEaseType::InElastic:
			return EaseInElastic(t);
		case EGFEaseType::OutElastic:
			return EaseOutElastic(t);
		case EGFEaseType::InOutElastic:
			return EaseInOutElastic(t);
		case EGFEaseType::InBounce:
			return EaseInBounce(t);
		case EGFEaseType::OutBounce:
			return EaseOutBounce(t);
		case EGFEaseType::InOutBounce:
			return EaseInOutBounce(t);
		case EGFEaseType::InBack:
			return EaseInBack(t);
		case EGFEaseType::OutBack:
			return EaseOutBack(t);
		case EGFEaseType::InOutBack:
			return EaseInOutBack(t);
	}
}

float FGFEasing::EaseWithParams(float t, EGFEaseType EaseType, float Param1, float Param2)
{
	if (Param1 == 0 && Param2 == 0)
	{
		return Ease(t, EaseType);
	}

	switch (EaseType)
	{
		default:
		case EGFEaseType::Linear:
			return EaseLinear(t);
		case EGFEaseType::Smoothstep:
			return EaseSmoothstep(t, Param1, Param2);
		case EGFEaseType::Stepped:
			return EaseStepped(t, Param1);
		case EGFEaseType::InSine:
			return EaseInSine(t);
		case EGFEaseType::OutSine:
			return EaseOutSine(t);
		case EGFEaseType::InOutSine:
			return EaseInOutSine(t);
		case EGFEaseType::InQuad:
			return EaseInQuad(t);
		case EGFEaseType::OutQuad:
			return EaseOutQuad(t);
		case EGFEaseType::InOutQuad:
			return EaseInOutQuad(t);
		case EGFEaseType::InCubic:
			return EaseInCubic(t);
		case EGFEaseType::OutCubic:
			return EaseOutCubic(t);
		case EGFEaseType::InOutCubic:
			return EaseInOutCubic(t);
		case EGFEaseType::InQuart:
			return EaseInQuart(t);
		case EGFEaseType::OutQuart:
			return EaseOutQuart(t);
		case EGFEaseType::InOutQuart:
			return EaseInOutQuart(t);
		case EGFEaseType::InQuint:
			return EaseInQuint(t);
		case EGFEaseType::OutQuint:
			return EaseOutQuint(t);
		case EGFEaseType::InOutQuint:
			return EaseInOutQuint(t);
		case EGFEaseType::InExpo:
			return EaseInExpo(t);
		case EGFEaseType::OutExpo:
			return EaseOutExpo(t);
		case EGFEaseType::InOutExpo:
			return EaseInOutExpo(t);
		case EGFEaseType::InCirc:
			return EaseInCirc(t);
		case EGFEaseType::OutCirc:
			return EaseOutCirc(t);
		case EGFEaseType::InOutCirc:
			return EaseInOutCirc(t);
		case EGFEaseType::InElastic:
			return EaseInElastic(t, Param1, Param2);
		case EGFEaseType::OutElastic:
			return EaseOutElastic(t, Param1, Param2);
		case EGFEaseType::InOutElastic:
			return EaseInOutElastic(t, Param1, Param2);
		case EGFEaseType::InBounce:
			return EaseInBounce(t);
		case EGFEaseType::OutBounce:
			return EaseOutBounce(t);
		case EGFEaseType::InOutBounce:
			return EaseInOutBounce(t);
		case EGFEaseType::InBack:
			return EaseInBack(t, Param1);
		case EGFEaseType::OutBack:
			return EaseOutBack(t, Param1);
		case EGFEaseType::InOutBack:
			return EaseInOutBack(t, Param1);
	}
}

float FGFEasing::EaseLinear(float t)
{
	return t;
}

float FGFEasing::EaseSmoothstep(float t, float x0, float x1)
{
	float x = FMath::Clamp<float>((t - x0) / (x1 - x0), 0.0f, 1.0f);
	return x * x * (3.0f - 2.0f * x);
}

float FGFEasing::EaseStepped(float t, int Steps)
{
	if (t <= 0)
	{
		return 0;
	}
	else if (t >= 1)
	{
		return 1;
	}
	else
	{
		return FMath::FloorToFloat(Steps * t) / Steps;
	}
}

float FGFEasing::EaseInSine(float t)
{
	return 1 - FMath::Cos(t * PI * .5f);
}

float FGFEasing::EaseOutSine(float t)
{
	return FMath::Sin(t * PI * .5f);
}

float FGFEasing::EaseInOutSine(float t)
{
	return 0.5f * (1 - FMath::Cos(t * PI));
}

float FGFEasing::EaseInQuad(float t)
{
	return t * t;
}

float FGFEasing::EaseOutQuad(float t)
{
	return t * (2 - t);
}

float FGFEasing::EaseInOutQuad(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2;
	}
	else
	{
		float m = t - 1;
		return 1 - m * m * 2;
	}
}

float FGFEasing::EaseInCubic(float t)
{
	return t * t * t;
}

float FGFEasing::EaseOutCubic(float t)
{
	float m = t - 1;
	return 1 + m * m * m;
}

float FGFEasing::EaseInOutCubic(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2 * t2;
	}
	else
	{
		float m = t - 1;
		return 1 + m * m * m * 4;
	}
}

float FGFEasing::EaseInQuart(float t)
{
	return t * t * t * t;
}

float FGFEasing::EaseOutQuart(float t)
{
	float m = t - 1;
	return 1 - m * m * m * m;
}

float FGFEasing::EaseInOutQuart(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2 * t2 * t2;
	}
	else
	{
		float m = t - 1;
		return 1 - m * m * m * m * 8;
	}
}

float FGFEasing::EaseInQuint(float t)
{
	return t * t * t * t * t;
}

float FGFEasing::EaseOutQuint(float t)
{
	float m = t - 1;
	return 1 + m * m * m * m * m;
}

float FGFEasing::EaseInOutQuint(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2 * t2 * t2 * t2;
	}
	else
	{
		float m = t - 1;
		return 1 + m * m * m * m * m * 16;
	}
}

float FGFEasing::EaseInExpo(float t)
{
	if (t <= 0)
	{
		return 0;
	}
	if (t >= 1)
	{
		return 1;
	}
	return FMath::Pow(2, 10 * (t - 1));
}

float FGFEasing::EaseOutExpo(float t)
{
	if (t <= 0)
	{
		return 0;
	}
	if (t >= 1)
	{
		return 1;
	}
	return 1 - FMath::Pow(2, -10 * t);
}

float FGFEasing::EaseInOutExpo(float t)
{
	if (t <= 0)
	{
		return 0;
	}
	if (t >= 1)
	{
		return 1;
	}
	if (t < 0.5f)
	{
		return FMath::Pow(2, 10 * (2 * t - 1) - 1);
	}
	else
	{
		return 1 - FMath::Pow(2, -10 * (2 * t - 1) - 1);
	}
}

float FGFEasing::EaseInCirc(float t)
{
	return 1 - FMath::Sqrt(1 - t * t);
}

float FGFEasing::EaseOutCirc(float t)
{
	float m = t - 1;
	return FMath::Sqrt(1 - m * m);
}

float FGFEasing::EaseInOutCirc(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return (1 - FMath::Sqrt(1 - t2 * t2)) * .5f;
	}
	else
	{
		float m = t - 1;
		return (FMath::Sqrt(1 - 4 * m * m) + 1) * .5f;
	}
}

float FGFEasing::EaseInElastic(float t, float Amplitude, float Period)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else
	{
		float m = t - 1;
		float s = Period / 4.0f;
		if (Amplitude > 1)
		{
			s = Period * FMath::Asin(1.0f / Amplitude) / (2.0f * PI);
		}

		return -(Amplitude * FMath::Pow(2, 10 * m) * FMath::Sin((m - s) * (2.0f * PI) / Period));
	}
}
// baked-in-parameters version
// float FCTween::EaseInElastic(float t)
// {
// 	float m = t - 1;
// 	return -FMath::Pow(2, 10 * m) * FMath::Sin((m * 40 - 3) * PI / 6);
// }

float FGFEasing::EaseOutElastic(float t, float Amplitude, float Period)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else
	{
		float s = Period / 4.0f;
		if (Amplitude > 1)
		{
			s = Period * FMath::Asin(1.0f / Amplitude) / (2.0f * PI);
		}
		return 1.0f + Amplitude * FMath::Pow(2, -10 * t) * FMath::Sin((t - s) * (2.0f * PI) / Period);
	}
}
// baked-in-parameters version
// float FCTween::EaseOutElastic(float t)
// {
// 	return 1 + FMath::Pow(2, 10 * (-t)) * FMath::Sin((-t * 40 - 3) * PI / 6);
// }
float FGFEasing::EaseInOutElastic(float t, float Amplitude, float Period)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else
	{
		float m = 2.0f * t - 1;
		float s = Period / 4.0f;
		if (Amplitude > 1)
		{
			s = Period * FMath::Asin(1.0f / Amplitude) / (2.0f * PI);
		}

		if (m < 0)
		{
			return .5f * -(Amplitude * FMath::Pow(2, 10 * m) * FMath::Sin((m - s) * (2.0f * PI) / Period));
		}
		else
		{
			return 1.0f + .5f * (Amplitude * FMath::Pow(2, -10 * t) * FMath::Sin((t - s) * (2.0f * PI) / Period));
		}
	}
}
// baked-in-parameters version
// float FCTween::EaseInOutElastic(float t)
// {
// 	float s = 2 * t - 1;
// 	float k = (80 * s - 9) * PI / 18;
// 	if (s < 0)
// 	{
// 		return -.5f * FMath::Pow(2, 10 * s) * FMath::Sin(k);
// 	}
// 	else
// 	{
// 		return 1 + .5f * FMath::Pow(2, -10 * s) * FMath::Sin(k);
// 	}
// }

float FGFEasing::EaseInBounce(float t)
{
	return 1 - EaseOutBounce(1 - t);
}

float FGFEasing::EaseOutBounce(float t)
{
	float t2;

	if (t < BOUNCE_K1)
	{
		return BOUNCE_K0 * t * t;
	}
	else if (t < BOUNCE_K2)
	{
		t2 = t - BOUNCE_K3;
		return BOUNCE_K0 * t2 * t2 + 0.75f;
	}
	else if (t < BOUNCE_K4)
	{
		t2 = t - BOUNCE_K5;
		return BOUNCE_K0 * t2 * t2 + 0.9375f;
	}
	else
	{
		t2 = t - BOUNCE_K6;
		return BOUNCE_K0 * t2 * t2 + 0.984375f;
	}
}

float FGFEasing::EaseInOutBounce(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return .5f - .5f * EaseOutBounce(1 - t2);
	}
	else
	{
		return .5f + .5f * EaseOutBounce(t2 - 1);
	}
}

float FGFEasing::EaseInBack(float t, float Overshoot)
{
	return t * t * ((Overshoot + 1) * t - Overshoot);
}

float FGFEasing::EaseOutBack(float t, float Overshoot)
{
	float m = t - 1;
	return 1 + m * m * (m * (Overshoot + 1) + Overshoot);
}

float FGFEasing::EaseInOutBack(float t, float Overshoot)
{
	float t2 = t * 2;
	float s = Overshoot * BACK_INOUT_OVERSHOOT_MODIFIER;
	if (t < .5f)
	{
		return t * t2 * (t2 * (s + 1) - s);
	}
	else
	{
		float m = t - 1;
		return 1 + 2 * m * m * (2 * m * (s + 1) + s);
	}
}