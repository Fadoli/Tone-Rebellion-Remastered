# Island roster

## `IWLocInfo` roster

The remake draws and allows clicks on initial and automatically recruited workers. Recruited subtype-0 workers use the same tribe-specific body and 16-frame leg animation as starting workers. Source-derived roster slot geometry, the `0x2f` alternate layout, and strict hit bounds are covered by `island_panel_info` tests. Some `FUN_0042704b` effects remain unmodeled, and this pane has no runtime comparison. Recruitment rules and evidence are in [`worker-recruitment.md`](../worker-recruitment.md); function anchors are in `[FUNCTION_GUIDE.md](../../../FUNCTION_GUIDE.md)`.

The world and selected-floater renderers use the `FUN_0042704b` combat-stat badge: frame `0x15 - min(FUN_00420f28(), 10)`. The remake now derives it from each floater's scaled `max_attack_points`, rather than the unrelated maximum HP. REA pseudocode confirms the draw path calls `FUN_00420f28` immediately before selecting the FLTINFO frame (`ev_6be020baefff8d7e9510035fec1974270f2919cf880938d2c93b33b2a43c683b`); `FUN_00420f28` scales the catalog's max-attack-points row by the trained level (`ev_63ad84d3d0d141fdb043c3a8bc27b373108b9f2ce92bfb42ea0a29510a0bb3b9`).
