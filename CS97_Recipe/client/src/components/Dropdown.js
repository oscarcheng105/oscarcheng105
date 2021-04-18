import React from 'react'
import { makeStyles, } from '@material-ui/core/styles';
import {Select as MuiSelect, MenuItem, TextField}  from '@material-ui/core'
import { useForm } from './components/useForm';
import Autocomplete from '@material-ui/lab/Autocomplete';


const useStyles = makeStyles(theme => ({
    root: {
        '& .MuiFormControl-root':{ //& is a selector symobl, . is for all classes
            width: '50%'
            ,margin: theme.spacing(1)
        }
    }
}))

const initialFieldValues = {
    recipeName: '',
    description: '',
    ingredients: [],
    recipeName: [],
    procedures: '',
    reviews:[],
    userName:localStorage.name,
}

export default function Dropdown(props){

    const classes = useStyles();

    const options = props.recipeList

    const{
        fieldValues,
        setFieldValues,
        handleInputChange,
    }=useForm(initialFieldValues)

    return (
        <div className={classes.root}>
          <Autocomplete
            multiple
            id="tags-standard"
            options={options}
            getOptionLabel={(option) => option.recipeName}
            renderInput={(params) => (
              <TextField
                {...params}
                variant="standard"
                label="Find Recipes with Selected Ingredients!"
                placeholder="Select an Ingredient:"
              />
            )}
          />
        </div>
      );

    

}