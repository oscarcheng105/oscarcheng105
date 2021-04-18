# Recipe App for COM SCI 97 Final Project

This is a full stack project.  
The frontend was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app) and [Material-UI](https://github.com/mui-org/material-ui).  
The backend is created with [Node.js](https://github.com/nodejs/node) and [Express.js](https://github.com/expressjs/express)  
The database we are using is [MongoDB](https://github.com/mongodb/mongo).  
  
## Setup
Before running the project, we need to update the config file in the backend.  
1. Go to `/api/config` and create a file config.env
```
cd api/config   
touch config.env   
```
2. Make according changes to config.env to connect your own database and google_oauth20 client_id/secret:  
```
PORT = 9000   
MONGO_URI = xxxxxx   
GOOGLE_CLIENT_ID = xxxxxx   
GOOGLE_CLIENT_SECRET = xxxxxx   
```

### For api (Backend)
1. Go to `/api` folder and install the packages needed   
```
cd api  
npm i   
```
2. To start the api
```
npm run dev  
```

### For Client (Frontend)
1. Go to `/client` folder and install the packages needed   
```
cd client  
npm i   
```
2. To start the client
```
npm run start  
```

The project should be located at [localhost](http://localhost:3000/).

## Things of Note

- feel free to fork and adjust to your needs/wants

## Demo Video
[YouTube](https://www.youtube.com/watch?v=NfoLUNmaS2A)  
[Google Drive](https://drive.google.com/file/d/1m9Dy2YriBvpb-BqFnoVn-HZcDMALy2iq/view?usp=sharing)
