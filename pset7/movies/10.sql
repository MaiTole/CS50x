SELECT name FROM people WHERE id IN
(SELECT person_id FROM directors JOIN movies ON directors.movie_id = movies.id WHERE movie_id IN
(SELECT movie_id FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE rating >= 9.0) )