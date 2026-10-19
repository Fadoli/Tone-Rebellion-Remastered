# Charge des floaters

## Observations REA

`FUN_004200d2` et `FUN_00420188` décrémentent tous deux le short floater `+0x22` d'une unité s'il est positif. `FUN_0041e569` appelle l'un ou l'autre dans ses états 5/6 à une échéance liée au compteur `+0x0d`. Evidence : `ev_defc789c0b60245827f728513227b55b51b1c7c1982906668e0af2cbf797527b`, `ev_553533bbf5c8d4499bedf5f6ce48839793b298ebdb5d2ceca0678846f8797f30`, `ev_ad87da66a016a70974e90562a87b7eca6a6dc530c460c334775e5c1c0d4fe4cb`.

La période de l'état 6 est `(record[+0x3e] - record[+0x38]) * record[+0x3c]`, après la résolution du record par `FUN_00464242`/`FUN_0045575c`. L'état 5 utilise une période nulle. Le compteur `+0x0d` est comparé à cette période, puis incrémenté à chaque appel de `FUN_0041e569`. Evidence : `ev_8ff344255e93e11221a945c320098477f5389530b14f2365d07333370f52b20f`.

## Limites pour le port

Le décompilateur n'a pas établi le caller runtime de `FUN_0041e569`, l'initialisation/réinitialisation de `+0x0d`, ni la correspondance de ses appels avec les ticks du remake. Les paramètres de `FUN_0045575c` ne correspondent pas aux six champs déjà modélisés dans `FloaterStats`. `FUN_004200d2` augmente aussi un short à `+8`; `FUN_00420188` en augmente un à `+0x20`. Ces champs et leurs effets aval ne sont pas reliés au compteur CHARGE. Donc le décrément est observé, mais sa planification ne doit pas être simulée à chaque tick sans résoudre ces liens.

Voir aussi [unités, panneaux de lieu et déplacement](island-units-and-movement.md) pour le rendu CHARGE (`+0x0c` comme garde, `+0x22` comme valeur affichée).
