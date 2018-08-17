#include "Frame.hpp"
#include "Storyboard.hpp"
#include "Time.hpp"
#include <algorithm>
#include <vector>
const auto fadeTime = 324;
const auto songStart = Time("00:01:746").ms;
const auto songEnd = Time("04:28:338").ms;
void setupBackground() {
	// Gets rid of beatmap background
	Storyboard::CreateSprite("aotonatsubg.jpg", Vector2::Zero, Layer::Background);
	// Solid color background
	auto const background = Storyboard::CreateSprite("!", Vector2::Zero, Layer::Background);
	background->ScaleVector(0, Time("04:30:507").ms, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
	// Side bars
	const auto borderPosition = 250;
	const auto borderScale = Vector2(1, Vector2::ScreenSize.y);
	auto const leftBorder = Storyboard::CreateSprite("@", Vector2(-borderPosition, 0), Layer::Background);
	leftBorder->Fade(songStart - fadeTime, songStart, 0, 1);
	leftBorder->ScaleVector(0, 0, borderScale, borderScale);
	leftBorder->Fade(songEnd, songEnd + fadeTime, 1, 0);
	auto const rightBorder = Storyboard::CreateSprite("@", Vector2(borderPosition, 0), Layer::Background);
	rightBorder->Fade(songStart - fadeTime, songStart, 0, 1);
	rightBorder->ScaleVector(0, 0, borderScale, borderScale);
	rightBorder->Fade(songEnd, songEnd + fadeTime, 1, 0);
}
std::vector<int> setupImages() {
	auto images = std::vector<int>(52);
	for (int i = 0; i < images.size(); ++i) {
		images[i] = i;
	}
	std::random_shuffle(images.begin(), images.end());
	return images;
}
std::string getRandomImage(std::vector<int>& images) {
	const auto value = images.back();
	images.pop_back();
	return std::to_string(value);
}
std::vector<Frame> setupFrames() {
	auto images = setupImages();
	const auto frames = std::vector<Frame>({
		Frame(getRandomImage(images), "a", Time("00:01:746").ms),
		Frame(getRandomImage(images), "b", Time("00:06:935").ms),
		Frame(getRandomImage(images), "c", Time("00:12:124").ms),
		Frame(getRandomImage(images), "d", Time("00:17:313").ms),
		Frame(getRandomImage(images), "", Time("00:22:502").ms),
		Frame(getRandomImage(images), "", Time("00:27:691").ms),
		Frame(getRandomImage(images), "", Time("00:32:881").ms),
		Frame(getRandomImage(images), "", Time("00:38:070").ms),
		Frame(getRandomImage(images), "", Time("00:46:501").ms),
		Frame(getRandomImage(images), "", Time("00:51:365").ms),
		Frame(getRandomImage(images), "", Time("00:56:555").ms),
		Frame(getRandomImage(images), "", Time("01:02:068").ms),
		Frame(getRandomImage(images), "", Time("01:07:257").ms),
		Frame(getRandomImage(images), "", Time("01:12:446").ms),
		Frame(getRandomImage(images), "", Time("01:17:636").ms),
		Frame(getRandomImage(images), "", Time("01:22:825").ms),
		Frame(getRandomImage(images), "", Time("01:28:014").ms),
		Frame(getRandomImage(images), "", Time("01:33:203").ms),
		Frame(getRandomImage(images), "", Time("01:38:392").ms),
		Frame(getRandomImage(images), "", Time("01:43:582").ms),
		Frame(getRandomImage(images), "", Time("01:48:771").ms),
		Frame(getRandomImage(images), "", Time("01:53:960").ms),
		Frame(getRandomImage(images), "", Time("01:59:149").ms),
		Frame(getRandomImage(images), "", Time("02:08:230").ms),
		Frame(getRandomImage(images), "", Time("02:13:419").ms),
		Frame(getRandomImage(images), "", Time("02:18:609").ms),
		Frame(getRandomImage(images), "", Time("02:23:798").ms),
		Frame(getRandomImage(images), "", Time("02:27:690").ms),
		Frame(getRandomImage(images), "", Time("02:31:582").ms),
		Frame(getRandomImage(images), "", Time("02:38:068").ms),
		Frame(getRandomImage(images), "", Time("02:43:257").ms),
		Frame(getRandomImage(images), "", Time("02:48:446").ms),
		Frame(getRandomImage(images), "", Time("02:53:636").ms),
		Frame(getRandomImage(images), "", Time("02:58:825").ms),
		Frame(getRandomImage(images), "", Time("03:04:014").ms),
		Frame(getRandomImage(images), "", Time("03:11:798").ms),
		Frame(getRandomImage(images), "", Time("03:16:987").ms),
		Frame(getRandomImage(images), "", Time("03:22:176").ms),
		Frame(getRandomImage(images), "", Time("03:27:365").ms),
		Frame(getRandomImage(images), "", Time("03:32:555").ms),
		Frame(getRandomImage(images), "", Time("03:37:744").ms),
		Frame(getRandomImage(images), "", Time("03:42:933").ms),
		Frame(getRandomImage(images), "", Time("03:48:122").ms),
		Frame(getRandomImage(images), "", Time("03:53:311").ms),
		Frame(getRandomImage(images), "", Time("03:58:500").ms),
		Frame(getRandomImage(images), "", Time("04:03:690").ms),
		Frame(getRandomImage(images), "", Time("04:08:879").ms),
		Frame(getRandomImage(images), "", Time("04:14:068").ms),
		Frame(getRandomImage(images), "", Time("04:19:257").ms),
	});
	return frames;
}
void positionFrames(const std::vector<Frame>& frames) {
	const auto yOffset = Vector2::ScreenSize.y * 0.5f;
	const auto endPosition = Vector2(0, yOffset * 2);
	const auto topPosition = Vector2(0, yOffset);
	const auto midPosition = Vector2::Zero;
	const auto botPosition = Vector2(0, -yOffset);
	const auto startPosition = Vector2(0, -yOffset * 2);
	const auto moveOffset = Vector2(0, 20.0f);
	auto topFrame = Frame();
	auto midFrame = Frame();
	auto botFrame = frames[0];
	botFrame.scale(songStart - fadeTime);
	botFrame.fade(songStart - fadeTime, songStart, 0, 1);
	auto newFrame = frames[1];
	newFrame.scale(songStart - fadeTime);
	newFrame.fade(songStart - fadeTime, songStart, 0, 1);
	for (int i = 0; i < frames.size(); ++i) {
		const auto timing = frames[i].timing;
		topFrame.move(timing - fadeTime, timing, topPosition + moveOffset, endPosition - moveOffset);
		midFrame.move(timing - fadeTime, timing, midPosition + moveOffset, topPosition - moveOffset);
		botFrame.move(timing - fadeTime, timing, botPosition + moveOffset, midPosition - moveOffset);
		newFrame.move(timing - fadeTime, timing, startPosition + moveOffset, botPosition - moveOffset);
		topFrame = midFrame;
		midFrame = botFrame;
		botFrame = newFrame;
		if (i + 2 < frames.size()) {
			newFrame = frames[i + 2];
			newFrame.scale(timing);
		}
		else {
			newFrame = Frame();
		}
		int nextTiming;
		if (i + 1 < frames.size()) {
			nextTiming = frames[i + 1].timing;
		}
		else {
			nextTiming = songEnd;
		}
		topFrame.move(timing, nextTiming - fadeTime, topPosition - moveOffset, topPosition + moveOffset);
		midFrame.move(timing, nextTiming - fadeTime, midPosition - moveOffset, midPosition + moveOffset);
		botFrame.move(timing, nextTiming - fadeTime, botPosition - moveOffset, botPosition + moveOffset);
	}
	frames[frames.size() - 1].fade(songEnd, songEnd + fadeTime, 1, 0);
	frames[frames.size() - 2].fade(songEnd, songEnd + fadeTime, 1, 0);

}
int main() {
	setupBackground();
	const auto frames = setupFrames();
	positionFrames(frames);
	Storyboard::Write(R"(X:\osu!\Songs\824592 Mrs GREEN APPLE - Ao to Natsu\Mrs. GREEN APPLE - Ao to Natsu (Haruto).osb)");
	return 0;
}