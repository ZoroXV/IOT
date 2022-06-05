<script>
  let mouseDown = true;
  function handleClick() {
    mouseDown = !mouseDown;
    if (mouseDown) {
      return;
    }
  
    fetch('http://localhost:5000/', {
      method: 'POST',
      headers: {
        Accept: 'application/json',
        }
      }).then();
  }
</script>

<div on:click={handleClick}>
  <input type="checkbox" id="toggle_checkbox">
  <label for="toggle_checkbox"></label>
</div>

<style>
#toggle_checkbox {
  display: none;
}

label {
  position: absolute;
  top: 50%;
  right: 0;
  left: 5%;
  display: block;
  width: 140px;
  height: 70px;
  margin: 0 auto;
  transform: translateY(-50%);
  cursor: pointer;
}

label:before {
  top: 8px;
  left: 8px;
  width: 54px;
  height: 54px;
  border: 3px solid #fb8122;
}

label:after {
  top: 0;
  right: 0;
  width: 140px;
  height: 70px;
  border: 3px solid #EEEEEE;
}

label:before,
label:after {
  content: "";
  position: absolute;
  border-radius: 50px;
  box-sizing: border-box;
  transition: 0.5s ease top, 0.5s ease left, 0.5s ease right, 0.5s ease width,
    0.5s ease height, 0.5s ease border-color;
}

#toggle_checkbox:checked + label:before {
  top: 0;
  left: 0;
  width: 140px;
  height: 70px;
  border-color: #EEEEEE;
}

#toggle_checkbox:checked + label:after {
  top: 8px;
  right: 8px;
  width: 54px;
  height: 54px;
  border-color: #fb8122;
}

</style>