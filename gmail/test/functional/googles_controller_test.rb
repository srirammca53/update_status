require 'test_helper'

class GooglesControllerTest < ActionController::TestCase
  setup do
    @google = googles(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:googles)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create google" do
    assert_difference('Google.count') do
      post :create, :google => @google.attributes
    end

    assert_redirected_to google_path(assigns(:google))
  end

  test "should show google" do
    get :show, :id => @google.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @google.to_param
    assert_response :success
  end

  test "should update google" do
    put :update, :id => @google.to_param, :google => @google.attributes
    assert_redirected_to google_path(assigns(:google))
  end

  test "should destroy google" do
    assert_difference('Google.count', -1) do
      delete :destroy, :id => @google.to_param
    end

    assert_redirected_to googles_path
  end
end
