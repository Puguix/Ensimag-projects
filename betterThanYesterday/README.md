# Better Than Yesterday

Better Than Yesterday (BTY) is a mobile app designed as a social media to help and keep people motivated on improving themselves with their friends.

### Frontend

The project uses Expo for development purpose, you can run the app with:

```shell
- cd frontend
- npm run android
- npm run ios
- npm run web
```

You can access the app for development via:

```shell
- cd frontend
- npx expo start
```

The project uses NativeWind (tailwindcss for react native), twin-macro-react-native-classnames and styled-components for the frontend.
It uses @react-navigation/native for the navigation.

### Backend

The backend uses node with express and sequelize (Object Relational Mapping).

To run the backend (it uses nodemon), generate the doc (with swagger), update the database:

```shell
- npm run startdev
- npm run doc
- npm run updatedb
```

To access the database:

```
sqlite3 bmt.sqlite
```
