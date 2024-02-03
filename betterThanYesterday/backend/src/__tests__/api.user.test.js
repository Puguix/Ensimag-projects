const app = require('../app')
const request = require('supertest')

describe('GET /api/users', () => {
  test('Test if get users works with initialized table user', async () => {
    const response = await request(app)
      .get('/api/users')
    expect(response.statusCode).toBe(200)
    expect(response.body.message).toBe('Returning users')
    expect(response.body.data.length).toBe(1)
  })
})
