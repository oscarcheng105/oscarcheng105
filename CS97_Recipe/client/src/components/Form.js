import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Grid from '@material-ui/core/Grid';
import { useForm } from './components/useForm';
import Controls from './components/controls/Controls';
import MenuItem from '@material-ui/core/MenuItem';
import * as tagsArray from "./tag/tagsArray.js"

const initialFieldValues = {
    recipeName: '',
    description: '',
    ingredients: '',
    tag: [],
    procedures: '',
    reviews:[],
    userName:localStorage.name,
}

const useStyles = makeStyles(theme => ({
    root: {
        '& .MuiFormControl-root':{ //& is a selector symobl, . is for all classes
            width: '80%'
            ,margin: theme.spacing(1)
        }
    }
}))

export default function RecipeForm(props) {
    const classes = useStyles();

    const{
        fieldValues,
        setFieldValues,
        handleInputChange,
    }=useForm(initialFieldValues)

    return(
        <form className = {classes.root}>
            <Grid container>
                <Grid item x5 = {5}>
                    <Controls.Input
                        name = "recipeName"
                        label='Recipe Name'
                        value={fieldValues.recipeName}
                        onChange= {handleInputChange}
                    />
                    <Controls.Input
                        name ="description"
                        label='Description'
                        value={fieldValues.description}
                        onChange= {handleInputChange}   
                    />
                    <Controls.Input
                        name = "ingredients"
                        label = "Ingredients Used"
                        value = {fieldValues.ingredients}
                        onChange = {handleInputChange}
                    />
                    <Controls.Select
                        name = "tag"
                        label = "Tag"
                        value = {fieldValues.tag}
                        onChange = {handleInputChange}
                        options = {tagsArray.getTagsArray()}
                    />
                    <Controls.Multiline
                        name = "procedures"
                        label = "Steps: "
                        value = {fieldValues.procedures}
                        onChange = {handleInputChange}
                    />
                    <div>
                        <Controls.Button
                        color = "primary"
                        size = "large"
                        text = "Submit"
                        onClick = {() => props.onCreateRecipe(fieldValues)}
                        />
                    </div>
                </Grid>
                <Grid item x5 = {5}></Grid>
            </Grid>
        </form>

    )
}

