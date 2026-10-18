# Tone Rebellion remake

Remake ind�pendant en C11, guid� par l�analyse statique et les ressources locales. Le binaire original reste une r�f�rence en lecture seule; il n�est pas ex�cut�.

## Construire et v�rifier

```powershell
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --parallel 4
ctest --test-dir build/release --output-on-failure
```

Ex�cutable Windows attendu : `ToneRebellion_Remake.exe` � c�t� de ce fichier. Les commandes de validation et les formats sont d�taill�s dans [Construction et validations](docs/build-and-validation.md).

## Documentation

- [Menu, carte et interface insulaire](docs/menu-and-island-ui.md)
- [D�marrage du monde et simulation initiale](docs/world-start.md)
- [Rendu des b�timents](docs/building-rendering.md)
- [Notes de rendu par �cran](GRAPHICS_RECONSTRUCTION.md)
- [Prochaines t�ches](TODO.md)
- [Traces de mouvement](MOVEMENT_REVERSE_ENGINEERING.md)
- [Guide fonctionnel et preuves d�origine](../FUNCTION_GUIDE.md)
