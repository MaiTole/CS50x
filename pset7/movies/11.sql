SELECT title FROM
movies JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON ratings.movie_id = stars.movie_id
JOIN people ON stars.person_id = people.id
where name = 'Chadwick Boseman' ORDER by rating DESC LIMIT 5
