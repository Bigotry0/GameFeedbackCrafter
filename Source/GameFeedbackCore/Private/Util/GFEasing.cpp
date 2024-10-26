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

float GFEasing::Ease(float t, EGFEase EaseType)
{
	switch (EaseType)
	{
		default:
		case EGFEase::Linear:
			return EaseLinear(t);
		case EGFEase::Smoothstep:
			return EaseSmoothstep(t);
		case EGFEase::Stepped:
			return EaseStepped(t);
		case EGFEase::InSine:
			return EaseInSine(t);
		case EGFEase::OutSine:
			return EaseOutSine(t);
		case EGFEase::InOutSine:
			return EaseInOutSine(t);
		case EGFEase::InQuad:
			return EaseInQuad(t);
		case EGFEase::OutQuad:
			return EaseOutQuad(t);
		case EGFEase::InOutQuad:
			return EaseInOutQuad(t);
		case EGFEase::InCubic:
			return EaseInCubic(t);
		case EGFEase::OutCubic:
			return EaseOutCubic(t);
		case EGFEase::InOutCubic:
			return EaseInOutCubic(t);
		case EGFEase::InQuart:
			return EaseInQuart(t);
		case EGFEase::OutQuart:
			return EaseOutQuart(t);
		case EGFEase::InOutQuart:
			return EaseInOutQuart(t);
		case EGFEase::InQuint:
			return EaseInQuint(t);
		case EGFEase::OutQuint:
			return EaseOutQuint(t);
		case EGFEase::InOutQuint:
			return EaseInOutQuint(t);
		case EGFEase::InExpo:
			return EaseInExpo(t);
		case EGFEase::OutExpo:
			return EaseOutExpo(t);
		case EGFEase::InOutExpo:
			return EaseInOutExpo(t);
		case EGFEase::InCirc:
			return EaseInCirc(t);
		case EGFEase::OutCirc:
			return EaseOutCirc(t);
		case EGFEase::InOutCirc:
			return EaseInOutCirc(t);
		case EGFEase::InElastic:
			return EaseInElastic(t);
		case EGFEase::OutElastic:
			return EaseOutElastic(t);
		case EGFEase::InOutElastic:
			return EaseInOutElastic(t);
		case EGFEase::InBounce:
			return EaseInBounce(t);
		case EGFEase::OutBounce:
			return EaseOutBounce(t);
		case EGFEase::InOutBounce:
			return EaseInOutBounce(t);
		case EGFEase::InBack:
			return EaseInBack(t);
		case EGFEase::OutBack:
			return EaseOutBack(t);
		case EGFEase::InOutBack:
			return EaseInOutBack(t);
	}
}

float GFEasing::EaseWithParams(float t, EGFEase EaseType, float Param1, float Param2)
{
	if (Param1 == 0 && Param2 == 0)
	{
		return Ease(t, EaseType);
	}

	switch (EaseType)
	{
		default:
		case EGFEase::Linear:
			return EaseLinear(t);
		case EGFEase::Smoothstep:
			return EaseSmoothstep(t, Param1, Param2);
		case EGFEase::Stepped:
			return EaseStepped(t, Param1);
		case EGFEase::InSine:
			return EaseInSine(t);
		case EGFEase::OutSine:
			return EaseOutSine(t);
		case EGFEase::InOutSine:
			return EaseInOutSine(t);
		case EGFEase::InQuad:
			return EaseInQuad(t);
		case EGFEase::OutQuad:
			return EaseOutQuad(t);
		case EGFEase::InOutQuad:
			return EaseInOutQuad(t);
		case EGFEase::InCubic:
			return EaseInCubic(t);
		case EGFEase::OutCubic:
			return EaseOutCubic(t);
		case EGFEase::InOutCubic:
			return EaseInOutCubic(t);
		case EGFEase::InQuart:
			return EaseInQuart(t);
		case EGFEase::OutQuart:
			return EaseOutQuart(t);
		case EGFEase::InOutQuart:
			return EaseInOutQuart(t);
		case EGFEase::InQuint:
			return EaseInQuint(t);
		case EGFEase::OutQuint:
			return EaseOutQuint(t);
		case EGFEase::InOutQuint:
			return EaseInOutQuint(t);
		case EGFEase::InExpo:
			return EaseInExpo(t);
		case EGFEase::OutExpo:
			return EaseOutExpo(t);
		case EGFEase::InOutExpo:
			return EaseInOutExpo(t);
		case EGFEase::InCirc:
			return EaseInCirc(t);
		case EGFEase::OutCirc:
			return EaseOutCirc(t);
		case EGFEase::InOutCirc:
			return EaseInOutCirc(t);
		case EGFEase::InElastic:
			return EaseInElastic(t, Param1, Param2);
		case EGFEase::OutElastic:
			return EaseOutElastic(t, Param1, Param2);
		case EGFEase::InOutElastic:
			return EaseInOutElastic(t, Param1, Param2);
		case EGFEase::InBounce:
			return EaseInBounce(t);
		case EGFEase::OutBounce:
			return EaseOutBounce(t);
		case EGFEase::InOutBounce:
			return EaseInOutBounce(t);
		case EGFEase::InBack:
			return EaseInBack(t, Param1);
		case EGFEase::OutBack:
			return EaseOutBack(t, Param1);
		case EGFEase::InOutBack:
			return EaseInOutBack(t, Param1);
	}
}

float GFEasing::EaseLinear(float t)
{
	return t;
}

float GFEasing::EaseSmoothstep(float t, float x0, float x1)
{
	float x = FMath::Clamp<float>((t - x0) / (x1 - x0), 0.0f, 1.0f);
	return x * x * (3.0f - 2.0f * x);
}

float GFEasing::EaseStepped(float t, int Steps)
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

float GFEasing::EaseInSine(float t)
{
	return 1 - FMath::Cos(t * PI * .5f);
}

float GFEasing::EaseOutSine(float t)
{
	return FMath::Sin(t * PI * .5f);
}

float GFEasing::EaseInOutSine(float t)
{
	return 0.5f * (1 - FMath::Cos(t * PI));
}

float GFEasing::EaseInQuad(float t)
{
	return t * t;
}

float GFEasing::EaseOutQuad(float t)
{
	return t * (2 - t);
}

float GFEasing::EaseInOutQuad(float t)
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

float GFEasing::EaseInCubic(float t)
{
	return t * t * t;
}

float GFEasing::EaseOutCubic(float t)
{
	float m = t - 1;
	return 1 + m * m * m;
}

float GFEasing::EaseInOutCubic(float t)
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

float GFEasing::EaseInQuart(float t)
{
	return t * t * t * t;
}

float GFEasing::EaseOutQuart(float t)
{
	float m = t - 1;
	return 1 - m * m * m * m;
}

float GFEasing::EaseInOutQuart(float t)
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

float GFEasing::EaseInQuint(float t)
{
	return t * t * t * t * t;
}

float GFEasing::EaseOutQuint(float t)
{
	float m = t - 1;
	return 1 + m * m * m * m * m;
}

float GFEasing::EaseInOutQuint(float t)
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

float GFEasing::EaseInExpo(float t)
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

float GFEasing::EaseOutExpo(float t)
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

float GFEasing::EaseInOutExpo(float t)
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

float GFEasing::EaseInCirc(float t)
{
	return 1 - FMath::Sqrt(1 - t * t);
}

float GFEasing::EaseOutCirc(float t)
{
	float m = t - 1;
	return FMath::Sqrt(1 - m * m);
}

float GFEasing::EaseInOutCirc(float t)
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

float GFEasing::EaseInElastic(float t, float Amplitude, float Period)
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

float GFEasing::EaseOutElastic(float t, float Amplitude, float Period)
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
float GFEasing::EaseInOutElastic(float t, float Amplitude, float Period)
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

float GFEasing::EaseInBounce(float t)
{
	return 1 - EaseOutBounce(1 - t);
}

float GFEasing::EaseOutBounce(float t)
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

float GFEasing::EaseInOutBounce(float t)
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

float GFEasing::EaseInBack(float t, float Overshoot)
{
	return t * t * ((Overshoot + 1) * t - Overshoot);
}

float GFEasing::EaseOutBack(float t, float Overshoot)
{
	float m = t - 1;
	return 1 + m * m * (m * (Overshoot + 1) + Overshoot);
}

float GFEasing::EaseInOutBack(float t, float Overshoot)
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