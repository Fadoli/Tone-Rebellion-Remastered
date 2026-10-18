# Trade, diplomatie et événements

## Trade

- **Observé :** grille de neuf valeurs, trois colonnes × trois lignes; clic gauche/droit ajuste de 10, bornes 0–1000. `TradeZERO` efface; `TradeDOIT` envoie des messages catégorie 3/type `0xb` aux destinataires non nuls puis efface l’offre.
- **Observé :** le dispatch type `0xb` prend les Hall source/cible depuis deux contextes joueur distincts; chaque quantité négative devient zéro et est bornée au stock signé du Hall source avant débit/crédit. Preuves : `ev_133e7da95213ee9e2afef5850bfdb622a53cde1a82d5ad9676b6717fd33abff2`, `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`, `ev_593f8a710f1ed28f08907d6644367309eb942d46a247531b989779fa3525c71f`.
- **Port :** `TradeDOIT` crée les demandes; le tick local les passe au helper récepteur puis les retire après application. Un transfert est borné au stock signé disponible du Hall source. Les demandes dont un Hall n’est pas résolu restent en tête de file.
- **Preuves UI :** `ev_3b5f4720935dc2a46a88ff1fbfea436d9ef271c9dc1729588ff092dad9112b44`, `ev_ce422c3de4f4cbea0f4a05e91a4bceeed3f8bd5614b6c565a9389730931e5f1c`.

## Diplomatie

- **Observé :** `IWDiplomacy` émet catégorie 3/sous-type 10 pour la cible non locale. Le dispatch inverse les mots correspondants dans les groupes joueur `+0xe8` ou `+0xd8`. Les états d’affichage utilisent les frames 21–23 de `DIPLOMA.SHP`; clés de texte et libellés visibles semblent inversés selon le code.
- **Port :** zones, choix d’état et outbox sont portés; bannières seulement pour les ouvriers initiaux, sans animation ni transport réseau.
- **Preuves :** `ev_83310289d91202d60603bd9f80ef78479a48b64c570e61ce5afd111af27eccb0`, `ev_b31952fff609b555e9e8c59eecea0d388c46aab20464cc9ff7bdc3ea7e0b5f`, `ev_bf0c6364cbdd6d347934dbdf3ecc156f6f17460cd80f9a1b49567d39fdcfcfb2`.

## PANIC et tâches

- **PANIC observé/porté :** sous-type 0 inverse bit 0 du mot d’île à `+0x29bc + joueur*4`; l’initialisation met ces mots à zéro. Le sens du bit reste inconnu. Preuves : `ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`, `ev_60cc3b805a032ead183ce15cfa0965bb14b5d6c84b45414f6d11fbbb2eaca75b`.
- La projection Tasks et les handlers de priorité/annulation sont documentés dans [island-tasks.md](island-tasks.md); producteurs et cycle de vie restent ouverts.

Pseudocodes : [batch 0008](../functions/0012_batch_0008.md), [batch 0013](../functions/0017_batch_0013.md).
