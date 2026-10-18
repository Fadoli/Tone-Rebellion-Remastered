# Panneaux Trade et Diplomatie

### Trade panel input and table

The Trade table uses the three source resource sheets in row order and the IWTrade pane-relative cell ranges from FUN_0043ec78. Left/right clicks adjust by 10 and clamp each value to 0..1000. TradeZERO clears all nine offers. TradeDOIT creates one outbound type-0xb request per other player with nonzero amounts, preserving the original recipient order, then clears the offer table. The remake retains those outgoing requests in GameSession; it does not apply them to Hall stock because multiplayer transport is not implemented. This is a source-derived partial UI port, not evidence of completed trade parity. See test_game_trade and [FUNCTION_GUIDE.md](../../../FUNCTION_GUIDE.md).

### Diplomacy panel

The IWDiplomacy panel uses the source frames, hover zones, recipient order, and captions described above. `FUN_0043e5aa` places one `FUN_00428191` floater icon for the local player and each displayed opponent; the remake draws each modeled initial worker at those anchors using body/legs frame 0. This is a startup-state approximation: later unit state and the helper's animation are unresolved. `GameSession` still records local toggles and outbound subtype-10 requests without simulating network transport. Tests cover icon anchors, hit zones, player order, toggles, and queue capacity.
