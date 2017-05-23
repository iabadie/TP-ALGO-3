# TP-ALGO-3
# Descargar repo:
1-Click en "clone or download"
2-Copiar el link
3- Abrir la consola y dirigirse a la carpeta donde se quiere clonar la carpeta del repo:
ej: cd Documentos/proyectos

4- usar el comando `git clone (url que se copio antes)`

se clona el repo en la carpeta `c:/Documentos/proyectos/TP-ALGO-3

5- `cd TP-ALGO-3` para entrar a la carpeta del repo.

# Crear una nueva branch

en la raiz del repo local, escribir `git checkout -b nombreDeLaBranchNueva` , esto crea una nueva "rama" para trabajar sin afectar al resto

# Commitear

Son como puntos de guardado de las branchs.
cada vez que se implementa algo, ej: una primitiva, se debe commitear para guardar los cambios.
primero se deben "almacenar los cambios con 
`git add .` , asi guarda todos los cambios
`git commit -m "algo"`   las comillas van y algo es una breve descripcion de que es el commit.

se puede ver el estado haciendo `git status`  color verde son los cambios sin guardar, color rojo son los cambios guardados. si commiteamos guarda "permanentemente" y ya no apareceran como cambios.

# Volver atras
Si realizamos cambios, no hicimos add y queremos volver a restaurar todo como estaba luego del ultimo commit, hacemos
`git checkout .`



# Cuando una branch este lista para ser corregida, luego del ultimo commit, hacemos
´git push origin HEAD`