#pragma once

namespace intel_jimmy {

static const int DIM1 = 7;
static const int DIMT = 2;
static const int DIM2 = 264;

static const char local_script[DIM1][DIM2] = {
		"#-- Keep it blank --#",
		"(nervous) Ummmm…excuse me Brian. Some of those innovators created me.",
		"That’s right BK, they do call you BK don’t they?",
		"I agree. I hate to be a bother, but do you mind if I take a photo so I can tweet it to my friends? I have this great app…",
		"Thanks!",
		"There are a lot of people here…",
		"#-- ENDOFLINE --#"
		// "What do you mean, human?",
		// "What do you mean human experiences, Brian? Technology has helped create me."
};

static const char local_tweet[DIMT][DIM2] = {
		"Hello%20%20world~%20%20:-)",
		"Jimmy@CES2014!!"
};

static const int DIMCMD = 277;

enum m_WM_STA {
	WM_STA_NONE = -1,
	WM_STA_ACT = 0,	// TODO: actions
	WM_STA_INFO,
	WM_STA_AUD,
	WM_STA_TWI,
	WM_STA_PIC,

	WM_STA_EXIT = 42
};

}
