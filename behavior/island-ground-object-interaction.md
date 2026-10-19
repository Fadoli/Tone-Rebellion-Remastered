# Interaction des objets posés sur l'île

## Ce que prouve le binaire

`IWLocInfo` ne transforme pas la sélection d'un objet au sol en ramassage.
Son action 6 demande au départ de saisir le site sélectionné, mais le prédicat
`FUN_0045f337(site, NULL)` exige que la source soit un emplacement du joueur
portant un ID de bâtiment `0x25..0x34` (sauf `0x28`), avec les gardes de flags,
Hall et ressources de la fonction. Un `PIT_Object` (`item=1`) échoue donc comme
source de cette action.

La seconde forme du prédicat accepte un site cible de classe 0, libre
(`owner=-1`) et visible par le joueur. Si son item vaut 1, le sélecteur de
forme `+0x24` doit être compris entre 5 et 33. `FUN_0045302a` place également
ces sites dans la liste des cibles. Le site `item=1` est donc une cible
d'interaction établie; cette preuve ne dit pas que son objet est ramassé.

## Séquence grab/place observée

1. `FUN_00441d3e`, événement `IWLocInfo` 6, vérifie l'action et l'état
   `mbHaveGrabbed`. Si aucun objet n'est tenu, elle valide le site sélectionné
   avec `FUN_0045f337(site, NULL)` puis envoie `0x48`; si un objet est déjà tenu,
   elle envoie `0x4a` (`ev_d72eed96013f16e8cecbd5772c71935e76feec78b9df2e8af58ccce46c4ada4e`).
2. `FUN_0042fa0f` convertit `0x48` en événement catégorie 3/sous-type 5 et
   `0x4a` en catégorie 3/sous-type 6. `FUN_00465793` route ces événements vers
   `FUN_0045f4f5` et `FUN_0045f5c5` (`ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`,
   `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`).
3. Le sous-type 5 revalide la source, débite les trois coûts calculés par
   `FUN_0045f2a1`, mémorise l'île et le site d'origine (`+0x13ba/+0x13bc`),
   puis active l'état tenu (`+0x13c0=1`)
   (`ev_598cfe2b014b15e607c8b41ac943b5dd6af4e3db3c818406a1653591e00c406a`).
4. Le sous-type 6 valide la cible avec `FUN_0045343b`. L'assemblage de
   `FUN_0045f5c5` confirme que le pointeur cible est passé dans `ECX` et que le
   site source mémorisé est l'argument. Quand la cible est un
   site libre de type 0 ou 1, cette routine écrit sur la cible l'ID et le
   propriétaire de l'objet tenu via `FUN_004528ca`, puis copie d'autres champs
   du site source. Une pose réussie efface `+0x13c0`; un retour sur le site
   d'origine restitue les coûts (`ev_29c00108fecaae10e34c3acd2f038be290b324679da3c2aa13b3a70825e8b4ae`,
   `ev_ded193af75b4663591b54cea28c51d70b7d2a0d987a2d7b891ee6f7cacdc8963`,
   `ev_46b3b31c81eecb2bc50884c4458f57e4c8020d7001de0c3ae0260c3a1b1d9185`).

Le helper de pose copie les champs vers la cible; son corps ne vide pas le site
source. Les effets de `FUN_004533fb` et les autres mutations indirectes doivent
être vérifiés avant de qualifier l'opération de déplacement ou de duplication.
Dans tous les cas, cette séquence ne crédite pas l'inventaire 5–33 et ne prouve
pas la collecte du `PIT_Object`.

## Inconnue restante

Le parseur `fltinf.txt` lit le bloc `pickup` dans `FUN_00454d1f`, mais aucun
consommateur n'est encore relié à un contact floater–`PIT_Object`. Le producteur
de l'événement catégorie 3/sous-type 4 qui crédite l'inventaire reste aussi
inconnu. Il faut établir cette transition et l'éventuelle mutation du record
`item=1` avant de porter le ramassage.

Evidences complémentaires : les références entrantes de `FUN_0045f337` montrent
les call-sites UI et les transactions grab/place, sans call-site de tick
floater (`ev_0fb01505c0a7e326de1d7e85aa13d4df42a1c47415115b384c04cc90f31f9a6d`).
Cette couverture n'exclut pas un autre mécanisme qui lirait directement les
records de site.
