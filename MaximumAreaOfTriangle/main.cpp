#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int Solve(std::vector<std::string> A) {
	auto IsR = [](char c) { return c == 'r'; };
	auto IsG = [](char c) { return c == 'g'; };
	auto IsB = [](char c) { return c == 'b'; };

	enum class Segment {
		kRG = 0,
		kRB,
		kGB,
		kCount
	};
	auto SegIndex = [](Segment seg) { return static_cast<int>(seg); };

	struct RGB {
		int r1{ -1 };
		int r2{ -1 };
		int g1{ -1 };
		int g2{ -1 };
		int b1{ -1 };
		int b2{ -1 };
	};
	

	std::vector<RGB> yExtremeVertices(A.front().size());
	std::vector<RGB> xExtremeVertices(A.size());
	auto SaveExVertex = [&IsR, &IsG, &IsB](RGB& dst, char vertex, int index) {
			if (IsR(vertex)) {
				dst.r1 = dst.r1 < 0 ? index : dst.r1;
				dst.r2 = index;
			} else if (IsG(vertex)) {
				dst.g1 = dst.g1 < 0 ? index : dst.g1;
				dst.g2 = index;
			} else if (IsB(vertex)) {
				dst.b1 = dst.b1 < 0 ? index : dst.b1;
				dst.b2 = index;
			}
	};

	for (int i = 0; i < A.size(); ++i) {
		const auto& xAxis = A[i];
		RGB rgb;
		for (int j = 0; j < xAxis.size(); ++j) {
			const auto& vertex = A[i][j];
			SaveExVertex(yExtremeVertices[j], vertex, i);
			SaveExVertex(rgb, vertex, j);
		}
		xExtremeVertices[i] = std::move(rgb);
	}

	std::vector<std::vector<int> > maxBases(yExtremeVertices.size());
	auto CalcMaxLen = [](int a1, int a2, int b1, int b2) {
		if (a1 < 0 || b1 < 0) {
			return 0;
		}

		int len1 = std::abs(a1 - b2);
		int len2 = std::abs(b1 - a2);

		return std::max(len1, len2) + 1;
	};
	auto CalcMaxSegment = [&CalcMaxLen](const RGB& rgb, const std::string& vertexes) {
		if (vertexes == "RG") {
			return CalcMaxLen(rgb.r1, rgb.r2, rgb.g1, rgb.g2);
		} else if (vertexes == "RB") {
			return CalcMaxLen(rgb.r1, rgb.r2, rgb.b1, rgb.b2);
		} else if (vertexes == "GB") {
			return CalcMaxLen(rgb.g1, rgb.g2, rgb.b1, rgb.b2);
		}
		return -1;
	};

	for (int i = 0; i < maxBases.size(); ++i) {
		auto& base = maxBases[i];
		base.resize(SegIndex(Segment::kCount));
		base[SegIndex(Segment::kRG)] = CalcMaxSegment(yExtremeVertices[i], "RG");
		base[SegIndex(Segment::kRB)] = CalcMaxSegment(yExtremeVertices[i], "RB");
		base[SegIndex(Segment::kGB)] = CalcMaxSegment(yExtremeVertices[i], "GB");
	}

	int maxArea = 0;
	auto CalcArea = [](int b, int h) { return std::round(0.5 * b * h); };

	for (int i = 0; i < xExtremeVertices.size(); ++i) {

		for (int j = 0; j < maxBases.size(); ++j) {
			const auto& leftBase = maxBases[j];
			const auto& rightBase = maxBases[maxBases.size() - 1 - j];

			{
				// Directed to the left.
				int hR = xExtremeVertices[i].r2 < 0 ? 0 : xExtremeVertices[i].r2 - j + 1;
				int hG = xExtremeVertices[i].g2 < 0 ? 0 : xExtremeVertices[i].g2 - j + 1;
				int hB = xExtremeVertices[i].b2 < 0 ? 0 : xExtremeVertices[i].b2 - j + 1;

				int areaHR = CalcArea(leftBase[SegIndex(Segment::kGB)], hR);
				int areaHG = CalcArea(leftBase[SegIndex(Segment::kRB)], hG);
				int areaHB = CalcArea(leftBase[SegIndex(Segment::kRG)], hB);

				maxArea = std::max(maxArea, areaHR);
				maxArea = std::max(maxArea, areaHG);
				maxArea = std::max(maxArea, areaHB);
			}

			{
				// Directed to the right.
				int hR = xExtremeVertices[i].r1 < 0 ? 0 : maxBases.size() - j - xExtremeVertices[i].r1;
				int hG = xExtremeVertices[i].g1 < 0 ? 0 : maxBases.size() - j - xExtremeVertices[i].g1;
				int hB = xExtremeVertices[i].b1 < 0 ? 0 : maxBases.size() - j - xExtremeVertices[i].b1;

				int areaHR = CalcArea(rightBase[SegIndex(Segment::kGB)], hR);
				int areaHG = CalcArea(rightBase[SegIndex(Segment::kRB)], hG);
				int areaHB = CalcArea(rightBase[SegIndex(Segment::kRG)], hB);

				maxArea = std::max(maxArea, areaHR);
				maxArea = std::max(maxArea, areaHG);
				maxArea = std::max(maxArea, areaHB);
			}
		}
	}
	return maxArea;
}

int main () {
	std::vector<std::string> ex = {"rrrrr", "rrrrg", "rrrrr", "bbbbb"};
	std::vector<std::string> ex2 = {"bbrbbb", "brgrbb", "rbbggb", "rggggr", "rrggrb", "grrbrg", "gbbrrg", "grgrbb", "bbbrgr", "bbrrgg", "rggrbg", "rrgggg", "ggbbgb", "grggbb", "rrrbrr", "rrrbrb", "bbbbbb", "rbbbrg", "ggbbbg", "ggbggr", "bggrgb", "bbrrrb", "rbrrbb", "brbgrg", "rbrrrg", "bbrrgg", "rbgrgg"};
	std::vector<std::string> ex3 = {"rrrbr", "ggrgb", "bbbrg", "rrgrr", "gbggb", "rbbgr", "rbgrg", "bbbgr", "ggbbb", "bggbr", "ggrbb", "grrrg", "rbrrg", "brrgr", "rrgbg", "bbrgr", "gbbbr", "rrbgb", "brbbr", "bgrrr", "bbggr", "rggbg", "bbggg", "gggbb", "bgbbg", "rrbgr", "rggrb", "grggr", "rggrr"};
	std::vector<std::string> ex4 = {"rbrrggggbbbrgrrbr", "bbrrgbrbrgbrrgbbg", "ggbrggrrgrrgbrrrg", "rrrbgggbbggrrbgbr", "bbggggrbrgggrrbgg", "rrrbbgbgrrbrrgrbg", "gbbbrgbggrgbbrbgg", "bgbgrgbrbrgbrgggr", "bgbggrrrbrrgbrgbb", "brbggbbrrbgbrrgrb", "ggbbgbbbgbrbbbgbg", "gbrrbgrbrbgrrrgbg", "bgbrbbgrgbgrrrbgr", "brrgggbbgrrbgrbbg", "bbbrrbbbrbggrrbbr", "rrrrbgrbgrrbbrbbr", "gbggggrrrbrbggbgg", "grbgbbgrggrrrgbbg", "grgggbggbrgrgrgrb", "ggrrgrbggbrbggrbr", "ggbbbrgrbgbrggrgb", "grgbggrbrrrgrbbbg", "bbrrbrrbgbrrggbgg", "rrgrrgbggbbbgbggr", "rgrbrbrbgrbrrrrgg", "rgrbrbgrgrggbbrgr", "brgrggrgrgbgrrggg", "grbggrrbbrrgrgbgg", "rgrbbrbrgggrgrrbg"};
	std::cout << Solve(ex)  << ", correct is 10" << std::endl;
	std::cout << Solve(ex2) << ", correct is 81" << std::endl;
	std::cout << Solve(ex3) << ", correct is 70" << std::endl;
	std::cout << Solve(ex4) << ", correct is 247" << std::endl;
	return 0;
}