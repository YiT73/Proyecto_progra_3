# # Programación III: Proyecto Final (2024-1)
## Integrantes 
* Yitzhak Abraham Namihas Millan
* Carla Viviana Molina Alvares
* Adrian Alonso Deza Luna Victoria
* Ary Werner Aron Rojas Durand
##  Nota
* Usar este csv para que el programa funcione correctamente https://docs.google.com/spreadsheets/d/18MZ9mRXSELpP4-y581p4fEtEbNjVVR0_aYJc0j_IQSU/edit?usp=sharing
* Video expplicando el projecto: https://drive.google.com/drive/folders/1utPGUda_sQZQn_9iNuvMZYc6b0Oic9kk?usp=drive_link
# Documentación del Código

## Proyecto: Streamflix

### Descripción General

El proyecto consiste en una aplicación para la gestión de usuarios y películas en un sistema de streaming llamado Streamflix. Los usuarios pueden registrarse, iniciar sesión, y gestionar listas de películas para ver más tarde o darles like. Además, se implementan funciones de búsqueda de películas y control de acceso basado en la edad del usuario.

### Archivos

1. `Usuario.h`
2. `PeliculaBuilder.h`
3. `busqueda.h`
4. `Pelicula.h`
5. `Nodo.h`
6. `GrafoPeliculas.h`
7. `ControlEdad.h`

---

## `Usuario.h`

### Descripción

- **Atributos Privados:**
  - `edad`: Edad del usuario.
  - `pwd`: Contraseña del usuario.
  - `nombre`: Nombre o nick del usuario.
  - `acceso`: Indicador de si el usuario ha iniciado sesión.
  - `tem`: Puntero estático para la implementación del patrón Singleton.
  - `verMasTarde`: Lista de películas para ver más tarde.
  - `peliculasLiked`: Lista de películas que el usuario ha dado like.

- **Constructor Privado:**
  - `Usuario()`: Solicita al usuario su nombre, edad, y contraseña, verificando la contraseña.

- **Métodos Públicos:**
  - `bool view()`: Muestra un mensaje de bienvenida si el usuario ha iniciado sesión.
  - `void iniciar_sesion()`: Permite al usuario iniciar sesión.
  - `static Usuario* get()`: Obtiene la instancia única de `Usuario` (patrón Singleton).
  - `int getEdad() const`: Devuelve la edad del usuario.
  - `void agregarVerMasTarde(const Pelicula& pelicula)`: Agrega una película a la lista de "ver más tarde".
  - `void mostrarVerMasTarde()`: Muestra las películas en la lista de "ver más tarde".
  - `void darLike(const Pelicula& pelicula)`: Agrega una película a la lista de "películas liked".
  - `void mostrarlike()`: Muestra las películas en la lista de "películas liked".
  - `const vector<Pelicula>& getPeliculasLiked() const`: Devuelve la lista de películas liked.

---

## `PeliculaBuilder.h`

### Descripción

- **Atributos Privados:**
  - `id`: ID de la película.
  - `titulo`: Título de la película.
  - `sinopsis`: Sinopsis de la película.
  - `tags`: Conjunto de etiquetas de la película.

- **Métodos Privados:**
  - `void limpiarTexto(std::string& texto)`: Elimina espacios en blanco adicionales del texto.

- **Métodos Públicos:**
  - `PeliculaBuilder& conId(string i)`: Asigna el ID de la película.
  - `PeliculaBuilder& conTitulo(std::string t)`: Asigna el título de la película.
  - `PeliculaBuilder& conSinopsis(std::string s)`: Asigna la sinopsis de la película.
  - `PeliculaBuilder& agregarTag(const std::string& tag)`: Agrega una etiqueta a la película.
  - `PeliculaBuilder& conTags(const std::unordered_set<std::string>& nuevasTags)`: Asigna un conjunto de etiquetas a la película.
  - `Pelicula construir()`: Construye y devuelve un objeto `Pelicula`.

---

## `busqueda.h`

### Descripción

- **Funciones:**
  - `void filtrarPeliculasPorEdad(vector<Pelicula>& peliculas)`: Filtra las películas según la edad del usuario.
  - `void mostrarResultados(vector<Pelicula>& resultados, int& indice, int limite = 5)`: Muestra los resultados de la búsqueda en lotes.
  - `void mostrarDetallesPelicula(Pelicula pelicula)`: Muestra los detalles de una película específica.
  - `void mostrarPeliculasSimilares(GrafoPeliculas& grafo)`: Muestra películas similares basadas en las películas liked del usuario.
  - `void realizarBusqueda(GrafoPeliculas& grafo)`: Permite al usuario realizar diferentes tipos de búsqueda de películas.

---

## `Pelicula.h`

### Descripción

- **Atributos Privados:**
  - `id`: ID de la película.
  - `titulo`: Título de la película.
  - `sinopsis`: Sinopsis de la película.
  - `tags`: Conjunto de etiquetas de la película.

- **Constructores:**
  - `Pelicula() = default;`: Constructor por defecto.
  - `Pelicula(string i, string t, string s, unordered_set<string> ta)`: Constructor con parámetros.

- **Métodos Públicos:**
  - `const string& getId() const`: Devuelve el ID de la película.
  - `const string& getTitulo() const`: Devuelve el título de la película.
  - `const string& getSinopsis() const`: Devuelve la sinopsis de la película.
  - `const unordered_set<string>& getTags() const`: Devuelve las etiquetas de la película.

---

## `Nodo.h`

### Descripción

- **Atributos Públicos:**
  - `id`: ID del nodo.
  - `pelicula`: Objeto `Pelicula` asociado al nodo.
  - `conexiones`: Conjunto de nodos conectados a este nodo.

- **Constructores:**
  - `Nodo(string id, Pelicula pelicula)`: Constructor con parámetros.

- **Métodos Públicos:**
  - `void agregarConexion(Nodo* otroNodo)`: Agrega una conexión a otro nodo.

---

## `GrafoPeliculas.h`

### Descripción

- **Atributos Privados:**
  - `unordered_map<string, Nodo*> nodos`: Mapa de nodos en el grafo, indexados por el ID del nodo.

- **Métodos Públicos:**
  - `void agregarNodo(string id, Pelicula pelicula)`: Agrega un nodo al grafo.
  - `void agregarConexion(string id1, string id2)`: Agrega una conexión entre dos nodos.
  - `vector<Pelicula> buscarPeliculasPorTag(const std::string& tag)`: Busca películas por etiqueta.
  - `Nodo* buscarNodo(string id)`: Busca un nodo por su ID.

---

## `ControlEdad.h`

### Descripción

- **Métodos Públicos:**
  - `static bool esAptaParaEdad(int edadUsuario, int edadRequerida)`: Verifica si una película es apta para la edad del usuario.
  - `static int calcularEdadRequerida(const string& clasificacion)`: Calcula la edad requerida según la clasificación de la película.

---

### Conclusión

El proyecto Streamflix proporciona una base sólida para la gestión de usuarios y películas en un sistema de streaming, con énfasis en la personalización y la experiencia del usuario. La implementación del patrón Singleton en la clase `Usuario` garantiza que cada usuario tenga una instancia única, mientras que el uso de gráficos para las películas permite la búsqueda eficiente y la recomendación de películas similares.
