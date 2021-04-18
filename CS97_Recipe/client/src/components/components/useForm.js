import React, {useState, useEffect} from 'react'
import { makeStyles } from '@material-ui/core/styles';

export function useForm(initialFieldValues){

    const[fieldValues, setFieldValues] = useState(initialFieldValues)

    const handleInputChange = e =>{ //e is default event handler for HTML
        const {name,value} = e.target
        setFieldValues({
            ...fieldValues,
            [name]: value
        })
    }

    return{

        fieldValues,
        setFieldValues,
        handleInputChange,
    }
    
}

const useStyles = makeStyles(theme => ({
    root: {
        '& .MuiFormControl-root':{ //& is a selector symobl, . is for all classes
            width: '80%'
            ,margin: theme.spacing(1)
        }
    }
}))

export function Form(props) {
    const classes = useStyles()
    return (
        <form className = {classes.root}>
            {props.children}
        </form>
    )

}