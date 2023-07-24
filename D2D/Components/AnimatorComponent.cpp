#include "stdafx.h"
#include "AnimatorComponent.h"

AnimatorComponent::AnimatorComponent(const shared_ptr<AnimationClip>& animClip, const string& name)
	:Component(name), currentAnimClip(animClip)
{
//	this->animClips.clear();
	animClips.emplace(animClip->GetClipName(), animClip);

//	for (auto& animClip : animClips)
//		dynamic_cast<TextureRect*>(owner)->SetSRV(animClip.second->GetSRV());
}

AnimatorComponent::AnimatorComponent(const vector<shared_ptr<AnimationClip>>& animClips, const string& name)
	:Component(name), currentAnimClip(animClips[0])
{
//	this->animClips.clear();

	for (const auto& animClip : animClips)
		this->animClips.emplace(animClip->GetClipName(), animClip);

//	for (auto& animClip : this->animClips)
//		dynamic_cast<TextureRect*>(owner)->SetSRV(animClip.second->GetSRV());
}

void AnimatorComponent::Update()
{
	if (bStop) return;

	if (deltaTime > currentAnimClip->GetPlayRate())
	{
		if (currentAnimClip->GetIsReverse() == false)	// �̹����� ������
		{
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex++);
			if (currentFrameIndex >= currentAnimClip->GetFrameCount())
			{
				if (currentAnimClip->GetIsLoop())
					currentFrameIndex = 0;
				else
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
			}
		}
		else	// �̹����� ������
		{
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex--);
			if (currentFrameIndex == UINT_MAX)
			{
				if (currentAnimClip->GetIsLoop())
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
				else
					currentFrameIndex = 0;
			}
		}

		deltaTime = 0.0f;
	}

	deltaTime += DELTA;
}

void AnimatorComponent::AddAnimClip(const shared_ptr<AnimationClip>& animClip)
{
	animClips.emplace(animClip->GetClipName(), animClip);
}

void AnimatorComponent::SetCurrentAnimClip(const wstring& clipName)
{
	if (clipName == currentAnimClip->GetClipName() && currentAnimClip->GetIsLoop() == true) return;

	const auto& iter = animClips.find(clipName);

	dynamic_cast<TextureRect*>(owner)->SetSRV(iter->second->GetSRV());

	if (iter != animClips.end())
	{
		currentAnimClip = iter->second;

		deltaTime = 0.0f;

		if (currentAnimClip->GetIsReverse())
			currentFrameIndex = currentAnimClip->GetLastFrameIndex();
		else
			currentFrameIndex = 0;

		currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
	}
}
