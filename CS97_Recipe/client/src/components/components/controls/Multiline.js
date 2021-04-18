import React from 'react'
import TextField from '@material-ui/core/TextField';

export default function Multiline(props){

    const {name, label, value, onChange} = props

    return(
        <TextField
            variant='outlined'
            label={label}
            name = {name}
            value={value}
            rowsMax={4}
            multiline
            onChange= {onChange}
        />
    )

}