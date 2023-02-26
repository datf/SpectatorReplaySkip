#include "pch.h"
#include "SpectatorReplaySkip.h"


BAKKESMOD_PLUGIN(SpectatorReplaySkip, "Skip replays when in spectator mode", plugin_version, 0)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void SpectatorReplaySkip::onLoad()
{
	_globalCvarManager = cvarManager;
	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.ReplayPlayback.ShouldPlayReplay", std::bind(&SpectatorReplaySkip::Skip, this));
}

void SpectatorReplaySkip::Skip()
{
	auto player = gameWrapper->GetPlayerController();
	if (player.IsNull()) { return; }
	auto pri = player.GetPRI();
	if (pri.IsNull()) { return; }
	auto spectating = pri.IsSpectator();
	if (spectating) {
		gameWrapper->ExecuteUnrealCommand("ReadyUp");
	}
}

void SpectatorReplaySkip::onUnload()
{
}