const app = require("../app");
const request = require("supertest");

describe("GET /users", () => {
    test("Test if get users works with initialized table user", async () => {
        const response = await request(app).get("/users");
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Returning users");
        expect(response.body.data.length).toBe(1);
    });
});

describe("POST /users", () => {
    test("Test if post user works", async () => {
        const response = await request(app).post("/users").send({
            username: "test",
        });
        expect(response.statusCode).toBe(201);
        expect(response.body.message).toBe("User added");
        const response2 = await request(app).get("/users");
        expect(response2.statusCode).toBe(200);
        expect(response2.body.message).toBe("Returning users");
        expect(response2.body.data.length).toBe(2);
    });
});

describe("DELETE /users", () => {
    test("Test if delete users works", async () => {
        const response = await request(app).delete("/users");
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Users deleted");
        const response2 = await request(app).get("/users");
        expect(response2.statusCode).toBe(200);
        expect(response2.body.message).toBe("Returning users");
        expect(response2.body.data.length).toBe(0);
    });
});

describe("GET /getjwtDeleg/gauthpau", () => {
    test("Test if user can get token", async () => {
        const response = await request(app).get("/getjwtDeleg/gauthpau");
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Token created: ");
        expect(response.body.signature);
    });
});

describe("GET /whoami", () => {
    test("Test if user can get its login from token", async () => {
        const response = await request(app)
            .get("/whoami")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Login: ");
        expect(response.body.signature);
    });
});

describe("GET /bmt/gauthpau/tags", () => {
    test("Test if user can get its tags", async () => {
        const response = await request(app)
            .get("/bmt/gauthpau/tags")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Returning tags");
        expect(response.body.data.length).toBe(1);
    });
});

describe("POST /bmt/gauthpau/tags", () => {
    test("Test if user can create a tag", async () => {
        const response = await request(app)
            .post("/bmt/gauthpau/tags")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            )
            .send({ name: "Front" });
        expect(response.statusCode).toBe(201);
        expect(response.body.message).toBe("Tag added");
    });
});

describe("GET /bmt/gauthpau/tags/2", () => {
    test("Test if user can get a tag by its id", async () => {
        const response = await request(app)
            .get("/bmt/gauthpau/tags/2")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Returning tag: 2");
    });
});

describe("PUT /bmt/gauthpau/tags/2", () => {
    test("Test if user can modify a tag", async () => {
        const response = await request(app)
            .put("/bmt/gauthpau/tags/2")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            )
            .send({ name: "Frontend" });
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Tag modified");
    });
});

describe("DELETE /bmt/gauthpau/tags/2", () => {
    test("Test if user can delete a tag", async () => {
        const response = await request(app)
            .delete("/bmt/gauthpau/tags/2")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Tag deleted");
    });
});

describe("GET /bmt/gauthpau/bookmarks", () => {
    test("Test if user get bookmarks", async () => {
        const response = await request(app)
            .get("/bmt/gauthpau/bookmarks")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Returning bookmarks");
    });
});

describe("POST /bmt/gauthpau/bookmarks", () => {
    test("Test if user can create a bookmark", async () => {
        const response = await request(app)
            .post("/bmt/gauthpau/bookmarks")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            )
            .send({ title: "Express", link: "www.express.com" });
        expect(response.statusCode).toBe(201);
        expect(response.body.message).toBe("Bookmark added");
    });
});

describe("GET /bmt/gauthpau/bookmarks/2", () => {
    test("Test if user can get a bookmark by its id", async () => {
        const response = await request(app)
            .get("/bmt/gauthpau/bookmarks/2")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Returning bookmark: 2");
    });
});

describe("PUT /bmt/gauthpau/bookmarks/2", () => {
    test("Test if user can modify a bookmark", async () => {
        const response = await request(app)
            .put("/bmt/gauthpau/tags")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            )
            .send({
                title: "Express",
                link: "www.express.com",
                description: "express documentation",
            });
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Bookmark modified");
    });
});

describe("DELETE /bmt/gauthpau/bookmarks/2", () => {
    test("Test if user can delete a bookmark", async () => {
        const response = await request(app)
            .delete("/bmt/gauthpau/bookmarks/2")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Bookmark deleted");
    });
});

describe("GET /bmt/gauthpau/tags/1/bookmarks", () => {
    test("Test if user can get bookmarks linked to a tag", async () => {
        const response = await request(app)
            .get("/bmt/gauthpau/tags/1/bookmarks")
            .set(
                "x-access-token",
                "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"
            );
        expect(response.statusCode).toBe(200);
        expect(response.body.message).toBe("Returning tag bookmarks");
    });
});
