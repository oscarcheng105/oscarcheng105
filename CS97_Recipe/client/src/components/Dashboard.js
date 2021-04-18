import React, { useEffect } from 'react';
import {useHistory} from 'react-router-dom';
import clsx from 'clsx';
import { makeStyles } from '@material-ui/core/styles';
import CssBaseline from '@material-ui/core/CssBaseline';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import IconButton from '@material-ui/core/IconButton';
import Container from '@material-ui/core/Container';
import ExitToAppIcon from '@material-ui/icons/ExitToApp';
import AddIcon from '@material-ui/icons/Add';
import { Button, TextField } from '@material-ui/core';
import TableSample from './TableSample';

import Popup from './components/Popup'
import RecipeForm from './Form.js'

const drawerWidth = 240;

const useStyles = makeStyles((theme) => ({
  root: {
    display: 'flex',
  },
  toolbar: {
    paddingRight: 24, // keep right padding when drawer closed
  },
  toolbarIcon: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'flex-end',
    padding: '0 8px',
    ...theme.mixins.toolbar,
  },
  appBar: {
    zIndex: theme.zIndex.drawer + 1,
    transition: theme.transitions.create(['width', 'margin'], {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.leavingScreen,
    }),
  },
  appBarShift: {
    marginLeft: drawerWidth,
    width: `calc(100% - ${drawerWidth}px)`,
    transition: theme.transitions.create(['width', 'margin'], {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.enteringScreen,
    }),
  },
  menuButton: {
    marginRight: 36,
  },
  menuButtonHidden: {
    display: 'none',
  },
  title: {
    maxWidth: '20%',
    flexGrow: 1,
  },
  drawerPaper: {
    position: 'relative',
    whiteSpace: 'nowrap',
    width: drawerWidth,
    transition: theme.transitions.create('width', {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.enteringScreen,
    }),
  },
  drawerPaperClose: {
    overflowX: 'hidden',
    transition: theme.transitions.create('width', {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.leavingScreen,
    }),
    width: theme.spacing(7),
    [theme.breakpoints.up('sm')]: {
      width: theme.spacing(9),
    },
  },
  appBarSpacer: theme.mixins.toolbar,
  content: {
    flexGrow: 1,
    height: '100vh',
    overflow: 'auto',
  },
  container: {
    paddingTop: theme.spacing(4),
    paddingBottom: theme.spacing(4),
  },
  paper: {
    padding: theme.spacing(2),
    display: 'flex',
    overflow: 'auto',
    flexDirection: 'column',
  },
  fixedHeight: {
    height: 240,
  },
  searchBar:{
    background: theme.palette.secondary,
    margin: 'auto',
    width: '50%',
    height: '50%',
    align: 'center',
  },
  inputText: {
    color: '#e3f2fd',
  },
  pageContent:{
    margin: theme.spacing(5),
    padding: theme.spacing(3),
  },

}));

export default function Dashboard() {
  const classes = useStyles();
  const [ingredientsArray, setIngredients] = React.useState( [ 
    {index: 0, name: "Meat", chk: [false, false, false, false]}, {index: 1, name: "Vegetables", chk: [false, false, false, false]},
    {index: 2, name: "Dairy", chk:[false,false,false,false]}, {index: 3, name: "Carbohydrates", chk: [false, false, false, false]},
    {index: 4, name: "Seafood", chk: [false, false, false, false]}, {index: 5, name: "Fruits", chk: [false, false, false, false]},
    {index: 6, name: "Condiments/Spices", chk: [false, false, false, false]}
  ])
  const [openPopup, setOpenPopup] = React.useState(false)

  const history = useHistory();
  const [recipes, setRecipes] = React.useState([]);
  const [searchValue, setSearchValue] = React.useState("");

  const handleSearchChange = (e) => {
    setSearchValue((e.target.value).toLowerCase());
    console.log(searchValue);
  }

   
  const fetchRecipe = async() => {
      await fetch('/recipe')
      .then(res => res.json())
      .then(data => {
          setRecipes(data);
      });
  }

  const createRecipe = async (info) => {
    try{
      await fetch("/dashboard", {
        method: "POST",
        body: JSON.stringify(info),
        headers: {
          "Content-Type": "application/json",
        }
        }).then(res => {
        if (res.ok) {
          console.log("Frond-End Post Recipe Success")
          setOpenPopup(false);
          fetchRecipe();
        }
      })
    }
    catch(err){
      console.log("Front-End Post Recipe Fail");
    }
  };
  
  const logout = () => {
      localStorage.clear();
      history.push("/");
  }

  useEffect(()=>{
    fetchRecipe();
    console.log("index changed!: ")
  }, [ingredientsArray])

  return (
    <div className={classes.root}>
      <CssBaseline />
      <AppBar position="absolute" className={clsx(classes.appBar)}>
        <Toolbar className={classes.toolbar}>
          <Typography component="h1" variant="h6" color="inherit" noWrap className={classes.title}>
            Welcome, {localStorage.getItem('name')}
          </Typography>
          <TextField
          placeholder = "Search Recipe or User Name:"

          variant ="filled"
          className = {classes.searchBar}
          name = "Search"
          value = {searchValue}
          onChange = {handleSearchChange}
          InputProps={{className: classes.inputText}}
          >
          </TextField>
          <Button color = "inherit" 
          onClick={() =>setOpenPopup(true)}>
            Add User Input Form
            <AddIcon/>
          </Button>
          <Popup
            title = "Recipe Form"
            openPopup = {openPopup}
            setOpenPopup = {setOpenPopup}
          >
            <RecipeForm onCreateRecipe = {createRecipe}/>
          </Popup>
          <IconButton color="inherit" onClick={() => logout()}
          >
            <ExitToAppIcon />
            Logout
          </IconButton>
        </Toolbar>
      </AppBar>
      <main className={classes.content}>
        <div className={classes.appBarSpacer} /> 
        <Container maxWidth="lg" className={classes.container}>
          <TableSample recipeList = {recipes} search = {searchValue}/>
        </Container>

      </main>
    </div>
  );
}