# Charge des floaters

## Observations REA

`FUN_004200d2` décrémente le short `+0x22` du record de catégorie qu'il reçoit; `FUN_00420188` décrémente le short `+0x22` du record de source qu'il reçoit. Ils incrémentent aussi respectivement `+0x08` et `+0x20`. `FUN_0041e569` appelle l'un ou l'autre dans ses états 5/6 à une échéance liée au compteur floater `+0x0d`. Ces décréments ne sont donc pas une consommation directe de `GameFloaterStart.charge_current`. Evidence : `ev_a27b3898fdda0df3a91d263e0dff2cbf700e9f778e29db2b5d27637e7f5b4f79`, `ev_18b2df9005c04d016bfaba1d338b7a4985a9c1b761a39d42720033e4ebc3b851`, `ev_8578fcc7430b99a9d136eb0b2ff8e2854d7c283d39d2eccf477e4abff89249b4`.

La période de l'état 6 est `(record[+0x3e] - record[+0x38]) * record[+0x3c]`, après la résolution du record par `FUN_00464242`/`FUN_0045575c`. L'état 5 utilise une période nulle. Le compteur floater `+0x0d` est comparé à cette période, puis incrémenté à chaque appel de `FUN_0041e569`. `FUN_00466ce2` itère les floaters actifs, dans une limite de 256 entrées et jusqu'au nombre de floaters chargé, et appelle cette routine une fois par floater présent. Evidence : `ev_8ff344255e93e11221a945c320098477f5389530b14f2365d07333370f52b20f`, `ev_4fe247fd506ce6e3b4aa658e561cef1aa8a957bdca3c1b7c2c28c976a4eb4376`.

## Limites pour le port

Les appels directs entrants vers `FUN_0041e569` ne sont pas référencés; le dispatch trouvé passe par un thunk depuis la boucle de `FUN_00466ce2`. L'initialisation/réinitialisation du timer `+0x0d` et l'appel de `FUN_00466ce2` par le rythme du jeu restent à établir. Les paramètres de `FUN_0045575c` ne correspondent pas aux six champs déjà modélisés dans `FloaterStats`. Les shorts `+0x08` et `+0x20` incrémentés par les helpers et leurs effets aval restent à mapper. Le remake ne décrémente donc plus le CHARGE du floater lors d'une attaque : cette consommation n'est pas étayée par la trace. La cadence de maintenance de charge reste à porter avec ses enregistrements catégorie/source, après avoir relié cette boucle au tick du remake.

Voir aussi [unités, panneaux de lieu et déplacement](island-units-and-movement.md) pour le rendu CHARGE (`+0x0c` comme garde, `+0x22` comme valeur affichée).
